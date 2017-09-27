#ifndef CONTEXT_H
#define CONTEXT_H

#include <QList>
#include <QMap>
#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include <QSettings>
#include <QSharedPointer>

#include "define.h"
#include "core_global.h"
#include "transaction.h"
#include "data/core-data.h"

#include <odb/database.hxx>
#include <odb/session.hxx>

class IPlugin;

class CORESHARED_EXPORT Context
{
public:
    ~Context();
    static Context &instance();
    QList<IPlugin*> plugins();
    IPlugin *plugin(const QString &pluginId);
    void loadPlugins();
    void openDb(const QString &path);
    odb::database *db() { return m_db; }
    QSettings *settings() { return m_settings; }
    bool dbOpened() { return m_dbOpened; }
    void destroy();
    QStringList defaultPerms();

    QSharedPointer<User> currentUser() const;
    void setCurrentUser(const QSharedPointer<User> &currentUser);

    odb::session &session();

    SeasonPtr currentSeason() const;
    void setCurrentSeason(const SeasonPtr &currentSeason);

    void checkNumberSeries();

private:
    Context();
    QList<IPlugin*> m_plugins;
    odb::database *m_db;
    QSettings *m_settings;
    bool m_dbOpened;
    odb::session m_session;
    QSharedPointer<User> m_currentUser;
    SeasonPtr m_currentSeason;

    QStringList m_solved;

    void checkDb(const QString &path);
    void checkSchema(const QSqlDatabase &db, const QMap<QString, int> &schemaMap);
    void solveDep(IPlugin *plugin, const QSqlDatabase &db, const QMap<QString, int> &schemaMap);
    void createSchema(IPlugin *plugin, const QSqlDatabase &db, const QMap<QString, int> &schemaMap);
    void checkPermissions();
    void checkSeason();
};

#endif // CONTEXT_H
