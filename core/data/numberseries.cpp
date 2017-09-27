#include "numberseries.h"
#include "../context.h"
#include "../iplugin.h"

NumberSeries::NumberSeries(QObject *parent) : QObject(parent)
{
    m_id = 0;
    m_lastNumber = 0;
}

int NumberSeries::id() const
{
    return m_id;
}

void NumberSeries::setId(int id)
{
    m_id = id;
}

QString NumberSeries::prefix() const
{
    return m_prefix;
}

void NumberSeries::setPrefix(const QString &prefix)
{
    m_prefix = prefix;
}

int NumberSeries::lastNumber() const
{
    return m_lastNumber;
}

void NumberSeries::setLastNumber(int lastNumber)
{
    m_lastNumber = lastNumber;
}

QString NumberSeries::pluginId() const
{
    return m_pluginId;
}

void NumberSeries::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;
}

QSharedPointer<Season> NumberSeries::season() const
{
    return m_season;
}

void NumberSeries::setSeason(const QSharedPointer<Season> &season)
{
    m_season = season;
}

QString NumberSeries::seasonName() const
{
    if (!m_season.isNull())
    {
        return m_season->name();
    }

    return "";
}

QString NumberSeries::pluginName() const
{
    IPlugin *plugin = Context::instance().plugin(m_pluginId);
    return plugin != NULL ? plugin->pluginName() : "";
}
