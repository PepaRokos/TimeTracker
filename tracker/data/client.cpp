#include "client.h"

Client::Client(QObject *parent) : ComboItem(parent)
{

}

int Client::id() const
{
    return m_id;
}

void Client::setId(int id)
{
    m_id = id;
}

QString Client::name() const
{
    return m_name;
}

void Client::setName(const QString &name)
{
    m_name = name;
}

QString Client::street() const
{
    return m_street;
}

void Client::setStreet(const QString &street)
{
    m_street = street;
}

QString Client::houseNumber() const
{
    return m_houseNumber;
}

void Client::setHouseNumber(const QString &houseNumber)
{
    m_houseNumber = houseNumber;
}

QString Client::city() const
{
    return m_city;
}

void Client::setCity(const QString &city)
{
    m_city = city;
}

QString Client::zipCode() const
{
    return m_zipCode;
}

void Client::setZipCode(const QString &zipCode)
{
    m_zipCode = zipCode;
}

QString Client::dic() const
{
    return m_dic;
}

void Client::setDic(const QString &dic)
{
    m_dic = dic;
}

QString Client::ic() const
{
    return m_ic;
}

void Client::setIc(const QString &ic)
{
    m_ic = ic;
}

bool Client::eq(ComboItem *other)
{
    Client *client = qobject_cast<Client*>(other);
    return client != nullptr && this->id() == client->id();
}

QString Client::toString()
{
    return m_name + ", " + m_street + " " + m_houseNumber + ", " + m_city;
}
