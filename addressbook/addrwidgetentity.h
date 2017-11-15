#ifndef ADDRWIDGETENTITY_H
#define ADDRWIDGETENTITY_H

#include <QObject>
#include <QSharedPointer>

#include "iaddressable.h"
#include "data/address.h"

class AddrWidgetEntity : public QObject, public IAddressable
{
    Q_OBJECT
    Q_PROPERTY(QString company READ company WRITE setCompany)
    Q_PROPERTY(QString ic READ ic WRITE setIc)
    Q_PROPERTY(QString dic READ dic WRITE setDic)
    Q_PROPERTY(QString street READ street WRITE setStreet)
    Q_PROPERTY(QString houseNumber READ houseNumber WRITE setHouseNumber)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode)
    Q_PROPERTY(QSharedPointer<QObject> addressId READ addressId WRITE setAddressId)

public:
    explicit AddrWidgetEntity(QObject *parent = 0);

signals:

public slots:

    // IAddressable interface
public:
    virtual QString company() const override;
    virtual void setCompany(const QString &company) override;
    virtual QString ic() const override;
    virtual void setIc(const QString &ic) override;
    virtual QString dic() const override;
    virtual void setDic(const QString &dic) override;
    virtual QString street() const override;
    virtual void setStreet(const QString &street) override;
    virtual QString houseNumber() const override;
    virtual void setHouseNumber(const QString &houseNumber) override;
    virtual QString city() const override;
    virtual void setCity(const QString &city) override;
    virtual QString zipCode() const override;
    virtual void setZipCode(const QString &zipCode) override;
    virtual AddressPtr addressIdPtr() const override;
    virtual void setAddressIdPtr(const AddressPtr &addressId) override;

    QSharedPointer<QObject> addressId() const;
    void setAddressId(const QSharedPointer<QObject> &addressId);

private:
    QString m_company;
    QString m_ic;
    QString m_dic;
    QString m_street;
    QString m_houseNumber;
    QString m_city;
    QString m_zipCode;
    AddressPtr m_addressId;
};

typedef QSharedPointer<AddrWidgetEntity> AddrWidgetEntityPtr;

#endif // ADDRWIDGETENTITY_H
