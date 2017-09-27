#ifndef USER_H
#define USER_H

#include "core-data.h"
#include "core_global.h"

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QDateTime>
#include <odb/core.hxx>
#include <odb/qt/list.hxx>

#pragma db object
class CORESHARED_EXPORT User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString login READ login WRITE setLogin)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool active READ active WRITE setActive)
    Q_PROPERTY(bool isAdmin READ isAdmin WRITE setIsAdmin)
    Q_PROPERTY(QDateTime lastModDate READ lastModDate WRITE setLastModDate)
    Q_PROPERTY(QDateTime createDate READ createDate WRITE setCreateDate)

public:
    User();


    int id() const;
    void setId(int id);

    QString login() const;
    void setLogin(const QString &login);

    QString password() const;
    void setPassword(const QString &password);

    QString name() const;
    void setName(const QString &name);

    QDateTime lastModDate() const;
    void setLastModDate(const QDateTime &lastModDate);

    QDateTime createDate() const;
    void setCreateDate(const QDateTime &createDate);

    bool active() const;
    void setActive(bool active);

    bool isAdmin() const;
    void setIsAdmin(bool isAdmin);

    QList<QSharedPointer<Role> > listRoles() const;
    void setListRoles(const QList<QSharedPointer<Role> > &listRoles);

    void addRole(QSharedPointer<Role> role);

    void clearRoles();


private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_login;
    QString m_password;
    QString m_name;
    QDateTime m_lastModDate;
    QDateTime m_createDate;
    bool m_active;
    bool m_isAdmin;
#pragma db value_not_null
    QOdbList<QSharedPointer<Role> > m_listRoles;
};

#endif // USER_H
