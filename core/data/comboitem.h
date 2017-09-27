#ifndef COMBOITEM_H
#define COMBOITEM_H

#include "core_global.h"
#include <QSharedPointer>
#include <QVariant>
#include <QObject>

class CORESHARED_EXPORT ComboItem : public QObject
{
    Q_OBJECT

public:
    explicit ComboItem(QObject *parent = NULL);
    ~ComboItem();

    virtual bool eq(ComboItem *other) = 0;
    virtual QString toString() = 0;
};

#endif // COMBOITEM_H
