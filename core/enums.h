#ifndef ENUMS_H
#define ENUMS_H
#include <QObject>

#include "core_global.h"

class CORESHARED_EXPORT Enums : public QObject
{
    Q_OBJECT

    Q_ENUMS(VatType)
    Q_ENUMS(Rounding)
public:

    enum VatType
    {
        NONE,
        HIGH,
        FIRST_LOWER,
        SECOND_LOWER
    };

    enum Rounding
    {
        R_NONE,
        R_UP,
        R_DOWN,
        R_MATH
    };

    Enums()
    {
    }

};
#endif // ENUMS_H
