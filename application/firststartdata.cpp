#include "firststartdata.h"

FirstStartData::FirstStartData(QObject *parent) : QObject(parent)
{

}

QString FirstStartData::dbFile() const
{
    return m_dbFile;
}

void FirstStartData::setDbFile(const QString &dbFile)
{
    m_dbFile = dbFile;
}

QString FirstStartData::login() const
{
    return m_login;
}

void FirstStartData::setLogin(const QString &login)
{
    m_login = login;
}

QString FirstStartData::password() const
{
    return m_password;
}

void FirstStartData::setPassword(const QString &password)
{
    m_password = password;
}

bool FirstStartData::defaultDbPath() const
{
    return m_defaultDbPath;
}

void FirstStartData::setDefaultDbPath(bool defaultDbPath)
{
    m_defaultDbPath = defaultDbPath;
}

bool FirstStartData::defaultAdmin() const
{
    return m_defaultAdmin;
}

void FirstStartData::setDefaultAdmin(bool defaultAdmin)
{
    m_defaultAdmin = defaultAdmin;
}

bool FirstStartData::singleUser() const
{
    return m_singleUser;
}

void FirstStartData::setSingleUser(bool singleUser)
{
    m_singleUser = singleUser;
}

