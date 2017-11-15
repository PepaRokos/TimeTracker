#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>
#include <QString>

#include <comboitem.h>
#include <odb/core.hxx>

#include "addressbook_global.h"

#pragma db object
class ADDRESSBOOKSHARED_EXPORT Address : public ComboItem
{
    Q_OBJECT
    Q_PROPERTY(QString company READ company WRITE setCompany)
    Q_PROPERTY(QString ic READ ic WRITE setIc)
    Q_PROPERTY(QString dic READ dic WRITE setDic)
    Q_PROPERTY(QString contactName READ contactName WRITE setContactName)
    Q_PROPERTY(QString street READ street WRITE setStreet)
    Q_PROPERTY(QString houseNumber READ houseNumber WRITE setHouseNumber)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode)
    Q_PROPERTY(QString email READ email WRITE setEmail)
    Q_PROPERTY(QString web READ web WRITE setWeb)
    Q_PROPERTY(QString note READ note WRITE setNote)

public:
    explicit Address(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QString company() const;
    void setCompany(const QString &company);

    QString ic() const;
    void setIc(const QString &ic);

    QString dic() const;
    void setDic(const QString &dic);

    QString contactName() const;
    void setContactName(const QString &contactName);

    QString street() const;
    void setStreet(const QString &street);

    QString houseNumber() const;
    void setHouseNumber(const QString &houseNumber);

    QString city() const;
    void setCity(const QString &city);

    QString zipCode() const;
    void setZipCode(const QString &zipCode);

    QString note() const;
    void setNote(const QString &note);

    QString email() const;
    void setEmail(const QString &email);

    QString web() const;
    void setWeb(const QString &web);

private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_company;
    QString m_ic;
    QString m_dic;
    QString m_contactName;
    QString m_email;
    QString m_web;
    QString m_street;
    QString m_houseNumbre;
    QString m_city;
    QString m_zipCode;
    QString m_note;

    // ComboItem interface
public:
    virtual bool eq(ComboItem *other) override;
    virtual QString toString() override;
};

typedef QSharedPointer<Address> AddressPtr;

#endif // ADDRESS_H
