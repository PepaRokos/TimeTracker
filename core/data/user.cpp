#include "user.h"

User::User()
{
}
int User::id() const
{
    return m_id;
}

void User::setId(int id)
{
    m_id = id;
}
QList<QSharedPointer<Role> > User::listRoles() const
{
    return m_listRoles;
}

void User::setListRoles(const QList<QSharedPointer<Role> > &listRoles)
{
    m_listRoles = listRoles;
}

void User::addRole(QSharedPointer<Role> role)
{
    m_listRoles.append(role);
}

void User::clearRoles()
{
    m_listRoles.clear();
}

QString User::login() const
{
    return m_login;
}

void User::setLogin(const QString &login)
{
    m_login = login;
}

QString User::password() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}

QString User::name() const
{
    return m_name;
}
void User::setName(const QString &name)
{
    m_name = name;
}

QDateTime User::lastModDate() const
{
    return m_lastModDate;
}
void User::setLastModDate(const QDateTime &lastModDate)
{
    m_lastModDate = lastModDate;
}

QDateTime User::createDate() const
{
    return m_createDate;
}
void User::setCreateDate(const QDateTime &createDate)
{
    m_createDate = createDate;
}

bool User::active() const
{
    return m_active;
}
void User::setActive(bool active)
{
    m_active = active;
}

bool User::isAdmin() const
{
    return m_isAdmin;
}
void User::setIsAdmin(bool isAdmin)
{
    m_isAdmin = isAdmin;
}











