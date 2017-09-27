#include "role.h"

Role::Role(QObject *parent) :
    QObject(parent)
{
}
int Role::id() const
{
    return m_id;
}

void Role::setId(int id)
{
    m_id = id;
}
QString Role::name() const
{
    return m_name;
}

void Role::setName(const QString &name)
{
    m_name = name;
}
QDateTime Role::lastModDate() const
{
    return m_lastModDate;
}

void Role::setLastModDate(const QDateTime &lastModDate)
{
    m_lastModDate = lastModDate;
}
QDateTime Role::createDate() const
{
    return m_createDate;
}

void Role::setCreateDate(const QDateTime &createDate)
{
    m_createDate = createDate;
}
bool Role::active() const
{
    return m_active;
}

void Role::setActive(bool active)
{
    m_active = active;
}
QList<QWeakPointer<User> > Role::listUsers() const
{
    return m_listUsers;
}

void Role::setListUsers(const QList<QWeakPointer<User> > &listUsers)
{
    m_listUsers = listUsers;
}
QList<QSharedPointer<Permission> > Role::listPermissions() const
{
    return m_listPermissions;
}

void Role::setListPermissions(const QList<QSharedPointer<Permission> > &listPermissions)
{
    m_listPermissions = listPermissions;
}

void Role::addPermission(QSharedPointer<Permission> perm)
{
    m_listPermissions.append(perm);
}

void Role::clearPermissions()
{
    m_listPermissions.clear();
}







