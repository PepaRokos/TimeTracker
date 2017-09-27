#include "permissionevaluator.h"

#include <QSharedPointer>

#include "data/core-data.h"
#include "context.h"

PermissionEvaluator::PermissionEvaluator(QObject *parent)
    :QObject(parent)
{
}

PermissionEvaluator::~PermissionEvaluator()
{   
}

bool PermissionEvaluator::hasPermission(const QString &pluginId, const QString &permission)
{
    if (Context::instance().currentUser()->isAdmin())
    {
        return true;
    }

    bool ret;
    QList<QSharedPointer<Role> > roles = Context::instance().currentUser()->listRoles();

    ret = std::find_if(ALL(roles), [&pluginId, &permission](QSharedPointer<Role> role) -> bool {
        foreach (QSharedPointer<Permission> perm, role->listPermissions()) {
            if (perm->pluginId() == pluginId && perm->permissionName() == permission) {
                return true;
            }
        }
        return false;
    }) != roles.end();

    if (!ret)
    {
        emit permissionDenied(permission);
    }

    return ret;
}

