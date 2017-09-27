#include "seasonservice.h"

#include "core-odb.hxx"

SeasonService::SeasonService()
{

}

QSharedPointer<Season> SeasonService::active()
{
    QList<QSharedPointer<Season> > seasons = all("active = 1");
    if (seasons.count() > 0)
    {
        return seasons[0];
    }

    return QSharedPointer<Season>();
}

void SeasonService::activate(QSharedPointer<Season> season)
{
    Transaction tx;

    foreach (QSharedPointer<Season> ses, all()) {
        ses->setActive(false);
        update(ses);
    }

    season->setActive(true);
    update(season);

    tx.commit();
}
