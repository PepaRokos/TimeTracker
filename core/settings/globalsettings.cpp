#include "globalsettings.h"
#include <define.h>

GlobalSettings::GlobalSettings(QObject *parent) : QObject(parent)
{
    m_ic = 0;
    m_vatHigh = 0;
    m_vatFirstLower = 0;
    m_vatSecondLower = 0;
    m_singleUser = false;
}

QString GlobalSettings::firmName() const
{
    return m_firmName;
}

void GlobalSettings::setFirmName(const QString &firmName)
{
    m_firmName = firmName;
}

QString GlobalSettings::street() const
{
    return m_street;
}

void GlobalSettings::setStreet(const QString &street)
{
    m_street = street;
}

QString GlobalSettings::houseNumber() const
{
    return m_houseNumber;
}

void GlobalSettings::setHouseNumber(const QString &houseNumber)
{
    m_houseNumber = houseNumber;
}

QString GlobalSettings::zipCode() const
{
    return m_zipCode;
}

void GlobalSettings::setZipCode(const QString &zipCode)
{
    m_zipCode = zipCode;
}

QString GlobalSettings::city() const
{
    return m_city;
}

void GlobalSettings::setCity(const QString &city)
{
    m_city = city;
}

int GlobalSettings::ic() const
{
    return m_ic;
}

void GlobalSettings::setIc(int IC)
{
    m_ic = IC;
}

QString GlobalSettings::dic() const
{
    return m_dic;
}

void GlobalSettings::setDic(const QString &dic)
{
    m_dic = dic;
}

bool GlobalSettings::vatPayer() const
{
    return m_vatPayer;
}

void GlobalSettings::setVatPayer(bool vatPayer)
{
    m_vatPayer = vatPayer;
}

QString GlobalSettings::logoPath() const
{
    return m_logoPath;
}

void GlobalSettings::setLogoPath(const QString &logoPath)
{
    m_logoPath = logoPath;
}
QDecDouble GlobalSettings::vatHigh() const
{
    return TO_DEC(m_vatHigh);
}

void GlobalSettings::setVatHigh(QDecDouble vatHigh)
{
    m_vatHigh = FROM_DEC(vatHigh);
}
QDecDouble GlobalSettings::vatFirstLower() const
{
    return TO_DEC(m_vatFirstLower);
}

void GlobalSettings::setVatFirstLower(QDecDouble vatFirstLower)
{
    m_vatFirstLower = FROM_DEC(vatFirstLower);
}
QDecDouble GlobalSettings::vatSecondLower() const
{
    return TO_DEC(m_vatSecondLower);
}

void GlobalSettings::setVatSecondLower(QDecDouble vatSecondLower)
{
    m_vatSecondLower = FROM_DEC(vatSecondLower);
}

QString GlobalSettings::email() const
{
    return m_email;
}

void GlobalSettings::setEmail(const QString &email)
{
    m_email = email;
}

QString GlobalSettings::web() const
{
    return m_web;
}

void GlobalSettings::setWeb(const QString &web)
{
    m_web = web;
}

QString GlobalSettings::phone() const
{
    return m_phone;
}

void GlobalSettings::setPhone(const QString &phone)
{
    m_phone = phone;
}

bool GlobalSettings::singleUser() const
{
    return m_singleUser;
}

void GlobalSettings::setSingleUser(bool singleUser)
{
    m_singleUser = singleUser;
}



