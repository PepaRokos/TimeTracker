#include <QDir>
#include <QApplication>
#include <QPluginLoader>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
#include <QDebug>
#include <QTranslator>

#include <odb/sqlite/database.hxx>

#include "core.h"
#include "coreplugin.h"
#include "users/users.h"
#include "roles/roles.h"
#include "permissionservice.h"
#include "seasonservice.h"
#include "numberseriesservice.h"

Context::~Context()
{
    this->destroy();
}

Context &Context::instance()
{
    static Context ctx;
    return ctx;
}

QList<IPlugin *> Context::plugins()
{
    return m_plugins;
}

IPlugin *Context::plugin(const QString &pluginId)
{
    QList<IPlugin*>::iterator it = std::find_if(ALL(m_plugins), [&pluginId](IPlugin *p) { return p->pluginId() == pluginId; });
    if (it != m_plugins.end())
    {
        return *it;
    }

    return NULL;
}

void Context::loadPlugins()
{
    IPlugin *corePlugin = new CorePlugin();
    m_plugins.append(corePlugin);
    m_plugins.append(new Users);
    m_plugins.append(new Roles);

    QDir pluginsDir(qApp->applicationDirPath() + PLUGIN_ROOT);

    foreach (QString fileName, pluginsDir.entryList(QStringList() << "*.so" << "*.dll")) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *p = pluginLoader.instance();

        if (p != NULL) {
            IPlugin *plugin = qobject_cast<IPlugin*>(p);
            if (plugin != NULL) {
                m_plugins.append(plugin);
                plugin->init(pluginLoader.metaData());
            }
        }
        else
        {
            qDebug() << pluginLoader.errorString();
        }
    }

    QString dbPath = m_settings->value("db/path", "").toString();
    if (!dbPath.isEmpty())
    {
        openDb(dbPath);
    }
}

void Context::openDb(const QString &path)
{
    if (m_db != NULL) {
        delete m_db;
        m_solved.clear();
        m_dbOpened = false;
    }

    checkDb(path);
    m_db = new odb::sqlite::database(path.toStdString());
    m_settings->setValue("db/path", path);
    m_dbOpened = true;

    checkPermissions();
    checkSeason();
    checkNumberSeries();
}

void Context::destroy()
{
    if (m_db != NULL)
    {
        delete m_db;
        m_db = NULL;
        m_dbOpened = false;
    }

    /*if (m_settings != NULL && m_settings->parent() == NULL)
    {
        delete m_settings;
    }*/

    foreach (IPlugin *plugin, m_plugins)
    {
        delete plugin;
    }
    m_plugins.clear();
}

QStringList Context::defaultPerms()
{
    return QStringList() << PERM_READ << PERM_ADD << PERM_EDIT << PERM_DELETE;
}

Context::Context()
{
    m_db = NULL;
    m_settings = new QSettings("bukova.info", "timetracker");
    m_dbOpened = false;
}

SeasonPtr Context::currentSeason() const
{
    return m_currentSeason;
}

void Context::setCurrentSeason(const SeasonPtr &currentSeason)
{
    m_currentSeason = currentSeason;
}

QSharedPointer<User> Context::currentUser() const
{
    return m_currentUser;
}

void Context::setCurrentUser(const QSharedPointer<User> &currentUser)
{
    m_currentUser = currentUser;
}

odb::session &Context::session()
{
    return m_session;
}

void Context::checkDb(const QString &path)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "check");
        db.setDatabaseName(path);
        db.open();
        QSqlQuery q(db);
        QString verSql = "SELECT pluginId, schemaVersion FROM system";
        QString createSysSql = "CREATE TABLE \"system\" (\"id\" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \"pluginId\" TEXT NULL, \"schemaVersion\" TEXT NULL, \"settings\" TEXT NULL)";

        if (q.exec(verSql))
        {
            QMap<QString, int> schemas;
            while (q.next())
            {
                schemas[q.value("pluginId").toString()] = q.value("schemaVersion").toInt();
            }
            checkSchema(db, schemas);
        }
        else
        {
            q.exec(createSysSql);
            checkSchema(db, QMap<QString, int>());
        }

        db.close();
    }
    QSqlDatabase::removeDatabase("check");
}

void Context::checkSchema(const QSqlDatabase &db, const QMap<QString, int> &schemaMap)
{
    foreach (IPlugin *plugin, m_plugins) {
        solveDep(plugin, db, schemaMap);
    }
}

void Context::solveDep(IPlugin *plugin, const QSqlDatabase &db, const QMap<QString, int> &schemaMap)
{
    foreach (QString dep, plugin->dependsOn()) {
        QList<IPlugin*>::iterator it = std::find_if(ALL(m_plugins), [&dep](IPlugin *p) { return p->pluginId() == dep; });

        if (it != m_plugins.end())
        {
            solveDep(*it, db, schemaMap);
        }
    }

    if (!m_solved.contains(plugin->pluginId()))
    {
        createSchema(plugin, db, schemaMap);
        m_solved.append(plugin->pluginId());
    }
}

void Context::createSchema(IPlugin *plugin, const QSqlDatabase &db, const QMap<QString, int> &schemaMap)
{
    if (!schemaMap.contains(plugin->pluginId()) || schemaMap[plugin->pluginId()] < plugin->schemaVersion())
    {
        int ver = schemaMap[plugin->pluginId()];

        for (int i = 0; i < plugin->schemas().count(); i++)
        {
            if (!schemaMap.contains(plugin->pluginId()) || i >= ver)
            {
                QString sql = plugin->schemas()[i];
                sql = sql.trimmed();
                QSqlQuery q(db);

                QStringList sqlList = sql.split(";");
                bool error = false;

                foreach (QString s, sqlList) {
                    if (!s.isEmpty() && !q.exec(s))
                    {
                        qDebug() << q.lastError().text();
                        error = true;
                    }
                }

                if (error)
                {
                    continue;
                }

                if (ver == 0 && i == 0)
                {
                    sql = "INSERT INTO system(pluginId, schemaVersion) VALUES('" + plugin->pluginId() + "', 1)";
                }
                else
                {
                    sql = "UPDATE system SET schemaVersion = " + QString::number(i + 1) + " WHERE pluginId = '" + plugin->pluginId() + "'";
                }
                q.exec(sql);
            }
        }
    }
}

void Context::checkPermissions()
{
    PermissionService permService;
    foreach (IPlugin *plugin, m_plugins) {
        foreach (QString perm, defaultPerms()) {
            QSharedPointer<Permission> p = permService.forNameAndPlugin(perm, plugin->pluginId());
            if (p.isNull())
            {
                QSharedPointer<Permission> nPerm(new Permission);
                nPerm->setPermissionName(perm);
                nPerm->setPluginId(plugin->pluginId());
                permService.save(nPerm);
            }
        }
    }

    permService.checkForAdmin();
}

void Context::checkSeason()
{
    SeasonService srv;
    QSharedPointer<Season> season = srv.active();

    if (season.isNull())
    {
        season = QSharedPointer<Season>(new Season());
        season->setName("<<new season>>");
        season->setValidFrom(QDate::currentDate());
        season->setActive(true);
        srv.save(season);
    }

    m_currentSeason = season;
}

void Context::checkNumberSeries()
{
    NumberSeriesService srv;
    SeasonService sesSrv;
    QSharedPointer<Season> curSeason = sesSrv.active();

    foreach (IPlugin *plugin, m_plugins) {
        if (plugin->hasNumberSeries())
        {
            QSharedPointer<NumberSeries> numSer = srv.forPlugin(plugin->pluginId());

            if (numSer.isNull())
            {
                numSer = QSharedPointer<NumberSeries>(new NumberSeries());
                numSer->setPrefix(plugin->numberSeriesPrefix());
                numSer->setPluginId(plugin->pluginId());
                numSer->setSeason(curSeason);

                srv.save(numSer);
            }
        }
    }
}
