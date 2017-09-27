#include "iservice.h"

IService::IService(QObject *parent) : QObject(parent)
{
}

IService::~IService()
{
}

void IService::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;
}

