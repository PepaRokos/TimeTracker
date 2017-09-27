#ifndef SEASONSERVICE_H
#define SEASONSERVICE_H

#include <QSharedPointer>

#include "data/season.h"
#include "service.h"
#include "core_global.h"

class CORESHARED_EXPORT SeasonService : public Service<Season>
{
public:
    SeasonService();
    QSharedPointer<Season> active();
    void activate(QSharedPointer<Season> season);
};

#endif // SEASONSERVICE_H
