#ifndef IADDRESSABLE_H
#define IADDRESSABLE_H

#include <QString>
#include <QSharedPointer>

#include "data/address.h"

class IAddressable {
public:
    virtual QString company() const = 0;
    virtual void setCompany(const QString &company) = 0;

    virtual QString ic() const = 0;
    virtual void setIc(const QString &ic) = 0;

    virtual QString dic() const = 0;
    virtual void setDic(const QString &dic) = 0;

    virtual QString street() const = 0;
    virtual void setStreet(const QString &street) = 0;

    virtual QString houseNumber() const = 0;
    virtual void setHouseNumber(const QString &houseNumber) = 0;

    virtual QString city() const = 0;
    virtual void setCity(const QString &city) = 0;

    virtual QString zipCode() const = 0;
    virtual void setZipCode(const QString &zipCode) = 0;

    virtual AddressPtr addressIdPtr() const = 0;
    virtual void setAddressIdPtr(const AddressPtr &address) = 0;
};

typedef QSharedPointer<IAddressable> IAddressablePtr;

#endif // IADDRESSABLE_H
