#include "system.h"

System::System()
{

}

System::~System()
{

}

int System::id() const
{
    return m_id;
}

void System::setId(int id)
{
    m_id = id;
}

QString System::pluginId() const
{
    return m_pluginId;
}

QString System::settings() const
{
    return m_settings;
}

void System::setSettings(const QString &settings)
{
    m_settings = settings;
}
