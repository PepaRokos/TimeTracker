#include "permission.h"

Permission::Permission(QObject *parent) :
    QObject(parent)
{
}
int Permission::id() const
{
    return m_id;
}

void Permission::setId(int id)
{
    m_id = id;
}
QString Permission::pluginId() const
{
    return m_pluginId;
}

void Permission::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;
}
QString Permission::permissionName() const
{
    return m_permissionName;
}

void Permission::setPermissionName(const QString &permissionName)
{
    m_permissionName = permissionName;
}
QDateTime Permission::lastModDate() const
{
    return m_lastModDate;
}

void Permission::setLastModDate(const QDateTime &lastModDate)
{
    m_lastModDate = lastModDate;
}
QDateTime Permission::createDate() const
{
    return m_createDate;
}

void Permission::setCreateDate(const QDateTime &createDate)
{
    m_createDate = createDate;
}
bool Permission::active() const
{
    return m_active;
}

void Permission::setActive(bool active)
{
    m_active = active;
}
QList<QWeakPointer<Role> > Permission::listRoles() const
{
    return m_listRoles;
}

void Permission::setListRoles(const QList<QWeakPointer<Role> > &listRoles)
{
    m_listRoles = listRoles;
}

void Permission::addRole(QSharedPointer<Role> role)
{
    m_listRoles.append(role);
}







