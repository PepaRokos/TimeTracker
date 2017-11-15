#ifndef ADDRESSSERVICE_H
#define ADDRESSSERVICE_H

#include <core.h>
#include <QObject>

#include "data/addressbook-data.h"
#include "iaddressable.h"
#include "addressbook_global.h"

class ADDRESSBOOKSHARED_EXPORT AddressService : public Service<Address>
{
public:
    AddressService();

    void copyAddress(AddressPtr address, IAddressablePtr target);
    void copyAddress(IAddressable *source, IAddressable *target);
};

#endif // ADDRESSSERVICE_H
