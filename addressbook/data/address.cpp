#include "address.h"

Address::Address(QObject *parent) : ComboItem(parent)
{

}

int Address::id() const
{
    return m_id;
}

void Address::setId(int id)
{
    m_id = id;
}

QString Address::company() const
{
    return m_company;
}

void Address::setCompany(const QString &company)
{
    m_company = company;
}

QString Address::ic() const
{
    return m_ic;
}

void Address::setIc(const QString &ic)
{
    m_ic = ic;
}

QString Address::dic() const
{
    return m_dic;
}

void Address::setDic(const QString &dic)
{
    m_dic = dic;
}

QString Address::contactName() const
{
    return m_contactName;
}

void Address::setContactName(const QString &contactName)
{
    m_contactName = contactName;
}

QString Address::street() const
{
    return m_street;
}

void Address::setStreet(const QString &street)
{
    m_street = street;
}

QString Address::houseNumber() const
{
    return m_houseNumbre;
}

void Address::setHouseNumber(const QString &houseNumbre)
{
    m_houseNumbre = houseNumbre;
}

QString Address::city() const
{
    return m_city;
}

void Address::setCity(const QString &city)
{
    m_city = city;
}

QString Address::zipCode() const
{
    return m_zipCode;
}

void Address::setZipCode(const QString &zipCode)
{
    m_zipCode = zipCode;
}

QString Address::note() const
{
    return m_note;
}

void Address::setNote(const QString &note)
{
    m_note = note;
}

QString Address::email() const
{
    return m_email;
}

void Address::setEmail(const QString &email)
{
    m_email = email;
}

QString Address::web() const
{
    return m_web;
}

void Address::setWeb(const QString &web)
{
    m_web = web;
}

bool Address::eq(ComboItem *other)
{
    Address *addr = qobject_cast<Address*>(other);

    if (addr != nullptr)
    {
        return addr == this || addr->id() == this->id();
    }

    return false;
}

QString Address::toString()
{
    return m_company + ", " + m_street + ", " + m_houseNumbre + ", " + m_city;
}
