#ifndef PERMISSIONSERVICE_H
#define PERMISSIONSERVICE_H

#include "service.h"
#include "data/core-data.h"
#include "core_global.h"
#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/query.hxx>
#include <odb/result.hxx>

#include <QList>
#include <QSharedPointer>
#include <QString>

class CORESHARED_EXPORT PermissionService : public Service<Permission>
{
public:
    PermissionService();
    ~PermissionService();

    QList<QSharedPointer<Permission> > forPlugin(const QString &pluginId);
    QSharedPointer<Permission> forNameAndPlugin(const QString &name, const QString &pluginId);
    bool checkLogin(const QString &login, const QString &password);
    QSharedPointer<User> loadUser(const QString &login);
    void checkForAdmin();
    QString encryptPassword(const QString &plainPasswd);
};

#endif // PERMISSIONSERVICE_H
