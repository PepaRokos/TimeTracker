#include "numberseriesservice.h"
#include "seasonservice.h"
#include "core-odb.hxx"

NumberSeriesService::NumberSeriesService()
{

}

QSharedPointer<NumberSeries> NumberSeriesService::forPluginAndSeason(QString pluginId, QSharedPointer<Season> season)
{
    QList<QSharedPointer<NumberSeries> > series = all(QString("pluginId = '%1' AND season = %2").arg(pluginId, QString::number(season->id())));

    if (!series.isEmpty())
    {
        return series[0];
    }

    return QSharedPointer<NumberSeries>();
}

QSharedPointer<NumberSeries> NumberSeriesService::forPlugin(QString pluginId)
{
    SeasonService sesSrv;
    QSharedPointer<Season> currentSeason = sesSrv.active();

    if (!currentSeason.isNull())
    {
        return forPluginAndSeason(pluginId, currentSeason);
    }

    return QSharedPointer<NumberSeries>();
}

QSharedPointer<NumberSeries> NumberSeriesService::nextForPlugin(QString pluginId)
{
    QSharedPointer<NumberSeries> numSer = forPlugin(pluginId);

    if (numSer.isNull())
    {
        return QSharedPointer<NumberSeries>();
    }

    numSer->setLastNumber(numSer->lastNumber() + 1);
    update(numSer);

    return numSer;
}

QList<QSharedPointer<NumberSeries> > NumberSeriesService::allForSeason(QSharedPointer<Season> season)
{
    return all(QString("season = %1").arg(QString::number(season->id())));
}

QString NumberSeriesService::nextStrForPlugin(QString pluginId)
{
    NumberSeriesPtr numSer = nextForPlugin(pluginId);
    QString numSerStr;
    numSerStr.sprintf("%s%05d", numSer->prefix().toStdString().c_str(), numSer->lastNumber());

    return numSerStr;
}
