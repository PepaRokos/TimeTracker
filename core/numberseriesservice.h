#ifndef NUMBERSERIESSERVICE_H
#define NUMBERSERIESSERVICE_H

#include "data/numberseries.h"
#include "data/season.h"
#include "service.h"
#include "core_global.h"

class CORESHARED_EXPORT NumberSeriesService : public Service<NumberSeries>
{
public:
    NumberSeriesService();

    QSharedPointer<NumberSeries> forPluginAndSeason(QString pluginId, QSharedPointer<Season> season);
    QSharedPointer<NumberSeries> forPlugin(QString pluginId);
    QSharedPointer<NumberSeries> nextForPlugin(QString pluginId);
    QList<QSharedPointer<NumberSeries> > allForSeason(QSharedPointer<Season> season);
    QString nextStrForPlugin(QString pluginId);
};

#endif // NUMBERSERIESSERVICE_H
