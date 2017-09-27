#include "settingsservice.h"

#include "core-odb.hxx"

#include <odb/core.hxx>
#include <odb/result.hxx>

SettingsService::SettingsService(QObject *parent)
    :IService(parent)
{
}

SettingsService::SettingsService(const QString &pluginId, QObject *parent)
    :IService(parent)
{
    m_pluginId = pluginId;
}

QSharedPointer<System> SettingsService::loadSystem()
{
    Service<System> srv;
    QList<QSharedPointer<System> > sysObj = srv.all("pluginId = '" + m_pluginId + "'");

    if (sysObj.isEmpty())
    {
        emit dbErrorUpdate("Error loading sys object");
        return QSharedPointer<System>();
    }

    return sysObj[0];
}

void SettingsService::saveSystem(const QJsonDocument &doc)
{
    QSharedPointer<System> sysObj = loadSystem();

    if (sysObj.isNull())
    {
        emit dbErrorUpdate("Error loading sys object");
        return;
    }

    sysObj->setSettings(QString(doc.toJson()));

    Service<System> srv;
    srv.update(sysObj);
}
