#include "addrwidgetentity.h"

AddrWidgetEntity::AddrWidgetEntity(QObject *parent) : QObject(parent)
{
}

QString AddrWidgetEntity::company() const
{
    return m_company;
}

void AddrWidgetEntity::setCompany(const QString &company)
{
    m_company = company;
}

QString AddrWidgetEntity::ic() const
{
    return m_ic;
}

void AddrWidgetEntity::setIc(const QString &ic)
{
    m_ic = ic;
}

QString AddrWidgetEntity::dic() const
{
    return m_dic;
}

void AddrWidgetEntity::setDic(const QString &dic)
{
    m_dic = dic;
}

QString AddrWidgetEntity::street() const
{
    return m_street;
}

void AddrWidgetEntity::setStreet(const QString &street)
{
    m_street = street;
}

QString AddrWidgetEntity::houseNumber() const
{
    return m_houseNumber;
}

void AddrWidgetEntity::setHouseNumber(const QString &houseNumber)
{
    m_houseNumber = houseNumber;
}

QString AddrWidgetEntity::city() const
{
    return m_city;
}

void AddrWidgetEntity::setCity(const QString &city)
{
    m_city = city;
}

QString AddrWidgetEntity::zipCode() const
{
    return m_zipCode;
}

void AddrWidgetEntity::setZipCode(const QString &zipCode)
{
    m_zipCode = zipCode;
}

AddressPtr AddrWidgetEntity::addressIdPtr() const
{
    return m_addressId;
}

void AddrWidgetEntity::setAddressIdPtr(const AddressPtr &addressId)
{
    m_addressId = addressId;
}

QSharedPointer<QObject> AddrWidgetEntity::addressId() const
{
    return m_addressId;
}

void AddrWidgetEntity::setAddressId(const QSharedPointer<QObject> &addressId)
{
    if (dynamic_cast<Address*>(addressId.data()) != nullptr)
    {
        m_addressId = qSharedPointerCast<Address, QObject>(addressId);
    }
}
