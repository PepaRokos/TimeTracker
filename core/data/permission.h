#ifndef PERMISSION_H
#define PERMISSION_H

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
class CORESHARED_EXPORT Permission : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pluginId READ pluginId WRITE setPluginId)
    Q_PROPERTY(QString permissionName READ permissionName WRITE setPermissionName)
    Q_PROPERTY(QDateTime lastModDate READ lastModDate WRITE setLastModDate)
    Q_PROPERTY(QDateTime createDate READ createDate WRITE setCreateDate)
    Q_PROPERTY(bool active READ active WRITE setActive)
public:
    explicit Permission(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QString pluginId() const;
    void setPluginId(const QString &pluginId);

    QString permissionName() const;
    void setPermissionName(const QString &permissionName);

    QDateTime lastModDate() const;
    void setLastModDate(const QDateTime &lastModDate);

    QDateTime createDate() const;
    void setCreateDate(const QDateTime &createDate);

    bool active() const;
    void setActive(bool active);

    QList<QWeakPointer<Role> > listRoles() const;
    void setListRoles(const QList<QWeakPointer<Role> > &listRoles);

    void addRole(QSharedPointer<Role> role);

private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_pluginId;
    QString m_permissionName;
    QDateTime m_lastModDate;
    QDateTime m_createDate;
    bool m_active;
#pragma db value_not_null inverse(m_listPermissions)
    QOdbList<QWeakPointer<Role> > m_listRoles;

};

#endif // PERMISSION_H
