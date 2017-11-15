#include "addressservice.h"

AddressService::AddressService()
{

}

void AddressService::copyAddress(AddressPtr address, IAddressablePtr target)
{
    Q_ASSERT(target != nullptr);

    target->setCompany(address->company());
    target->setIc(address->ic());
    target->setDic(address->dic());
    target->setStreet(address->street());
    target->setHouseNumber(address->houseNumber());
    target->setCity(address->city());
    target->setZipCode(address->zipCode());
    target->setAddressIdPtr(address);
}

void AddressService::copyAddress(IAddressable* source, IAddressable* target)
{
    target->setCompany(source->company());
    target->setIc(source->ic());
    target->setDic(source->dic());
    target->setStreet(source->street());
    target->setHouseNumber(source->houseNumber());
    target->setCity(source->city());
    target->setZipCode(source->zipCode());
    target->setAddressIdPtr(source->addressIdPtr());
}
