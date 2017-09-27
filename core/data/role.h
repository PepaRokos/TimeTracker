#ifndef ROLE_H
#define ROLE_H

#include "core-data.h"
#include "core_global.h"

#include <QObject>
#include <QSharedPointer>
#include <QList>
#include <QWeakPointer>
#include <QDateTime>
#include <odb/core.hxx>
#include <odb/qt/list.hxx>

#pragma db object
class CORESHARED_EXPORT Role : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QDateTime lastModDate READ lastModDate WRITE setLastModDate)
    Q_PROPERTY(QDateTime createDate READ createDate WRITE setCreateDate)
    Q_PROPERTY(bool active READ active WRITE setActive)
public:
    explicit Role(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QDateTime lastModDate() const;
    void setLastModDate(const QDateTime &lastModDate);

    QDateTime createDate() const;
    void setCreateDate(const QDateTime &createDate);

    bool active() const;
    void setActive(bool active);

    QList<QWeakPointer<User> > listUsers() const;
    void setListUsers(const QList<QWeakPointer<User> > &listUsers);

    QList<QSharedPointer<Permission> > listPermissions() const;
    void setListPermissions(const QList<QSharedPointer<Permission> > &listPermissions);

    void addPermission(QSharedPointer<Permission> perm);
    void clearPermissions();

private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_name;
    QDateTime m_lastModDate;
    QDateTime m_createDate;
    bool m_active;
#pragma db value_not_null inverse(m_listRoles)
    QOdbList<QWeakPointer<User> > m_listUsers;
#pragma db value_not_null
    QOdbList<QSharedPointer<Permission> > m_listPermissions;
};

#endif // ROLE_H
