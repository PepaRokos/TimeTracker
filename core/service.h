#ifndef SERVICE_H
#define SERVICE_H

#include <QList>
#include <QSharedPointer>
#include <QString>
#include <QEventLoop>
#include <QApplication>

#include <odb/core.hxx>
#include <odb/transaction.hxx>
#include <odb/database.hxx>
#include <odb/result.hxx>

#include "core_global.h"
#include "context.h"
#include "iservice.h"
#include "permissionevaluator.h"
#include "iimporter.h"
#include "iimportprogress.h"

#include "transaction.h"

template<class T>
class Service : public IService
{
public:
    explicit Service(QObject *parent = NULL) :IService(parent) { }

    explicit Service(const QString &pluginId) {
        m_pluginId = pluginId;
    }

    QList<QSharedPointer<T> > all(const QString &where = "") {
        QList<QSharedPointer<T> > ret;

        if (!checkPermission(PERM_READ)) {
            return ret;
        }

        odb::database *db = Context::instance().db();

        Q_ASSERT(db);

        Transaction tx;

        try
        {
            odb::result<T> res;

            if (where.isEmpty())
            {
                res = db->template query<T>();
            }
            else
            {
                res = db->template query<T>(where.toStdString());
            }

            for (typename odb::result<T>::iterator it = res.begin(); it != res.end(); it++) {
                ret.append(it.load());
            }

            tx.commit();
        }
        catch (const odb::exception &ex)
        {
            emit dbError(ex.what());
        }

        return ret;
    }

    void save(QSharedPointer<T> entity) {
        if (!checkPermission(PERM_ADD)) {
            return;
        }

        odb::database *db = Context::instance().db();

        Q_ASSERT(db);

        Transaction tx;

        addDateAndUser(entity, true);

        try
        {
            db->persist(entity);
            tx.commit();
        }
        catch (const odb::exception &ex)
        {
            emit dbError(ex.what());
            emit dbErrorUpdate(ex.what());
            return;
        }

        emit dataChanged();
    }

    void update(QSharedPointer<T> entity) {
        if (!checkPermission(PERM_EDIT)) {
            return;
        }

        odb::database *db = Context::instance().db();

        Q_ASSERT(db);

        Transaction tx;

        addDateAndUser(entity, false);

        try
        {
            db->update(entity);
            tx.commit();
        }
        catch (const odb::exception &ex)
        {
            emit dbError(ex.what());
            emit dbErrorInsert(ex.what());
            return;
        }

        emit dataChanged();
    }

    QSharedPointer<T> loadById(int id) {
        QSharedPointer<T> entity;

        /*if (!checkPermission(PERM_READ)) {
            return entity;
        }*/

        odb::database *db = Context::instance().db();

        Q_ASSERT(db);

        Transaction tx;

        try
        {
            entity = db->template load<T>(id);
            tx.commit();
        }
        catch (const odb::exception &ex)
        {
            emit dbError(ex.what());
            emit dbErrorRead(ex.what());
        }

        return entity;
    }

    QSharedPointer<T> reload(int id) {
        odb::database *db = Context::instance().db();

        Q_ASSERT(db);

        Context::instance().session().cache_erase<T>(*db, id);
        return loadById(id);
    }

    void erase(QSharedPointer<T> entity) {
        if (!checkPermission(PERM_DELETE)) {
            return;
        }

        odb::database *db = Context::instance().db();

        Q_ASSERT(db);

        Transaction tx;

        try
        {
            db->erase(entity);
            tx.commit();
        }
        catch (const odb::exception &ex)
        {
            emit dbError(ex.what());
            emit dbErrorDelete(ex.what());
        }
    }

    bool importData(IImporter *importer, IImportProgress *progress = NULL) {
        int count = importer->recordCount();

        if (importer->isError()) {
            return false;
        }

        for (int i = 0; i < count - 1; i++) {
            QSharedPointer<QObject> qentity = importer->nextRecord();

            if (importer->isError() || qentity.isNull()) {
                return false;
            }

            QSharedPointer<T> entity = qentity.dynamicCast<T>();
            if (!entity.isNull()) {
                this->save(entity);
            }
            else
            {
                return false;
            }

            qApp->processEvents();

            if (progress != NULL && progress->terminate())
            {
                return true;
            }

            if (progress != NULL)
            {
                progress->updateProgress(i * 100 / count);
            }
        }

        return true;
    }

protected:
    bool checkPermission(const QString &permission) {
        if (!m_pluginId.isEmpty()) {
            PermissionEvaluator ev;
            if (!ev.hasPermission(m_pluginId, permission)) {
                emit permissionDenied(permission);
                return false;
            }
        }

        return true;
    }

    void addDateAndUser(QSharedPointer<T> entity, bool creating) {

        T *inner = entity.data();
        QObject *obj = dynamic_cast<QObject*>(inner);

        if (obj == NULL)
        {
            return;
        }

        if (creating && !Context::instance().currentUser().isNull())
        {
            obj->setProperty("createdBy", Context::instance().currentUser()->login());
            obj->setProperty("created", QDateTime::currentDateTime());
        }
        else if (!Context::instance().currentUser().isNull())
        {
            obj->setProperty("updatedBy", Context::instance().currentUser()->login());
            obj->setProperty("updated", QDateTime::currentDateTime());
        }
    }
};

#endif // SERVICE_H
