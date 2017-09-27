#ifndef CLIENT_H
#define CLIENT_H

#include "tracker-data.h"

#include <QObject>
#include <odb/core.hxx>
#include <comboitem.h>

#pragma db object
class Client : public ComboItem
{
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString ic READ ic WRITE setIc)
    Q_PROPERTY(QString dic READ dic WRITE setDic)
    Q_PROPERTY(QString street READ street WRITE setStreet)
    Q_PROPERTY(QString houseNumber READ houseNumber WRITE setHouseNumber)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode)

    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString street() const;
    void setStreet(const QString &street);

    QString houseNumber() const;
    void setHouseNumber(const QString &houseNumber);

    QString city() const;
    void setCity(const QString &city);

    QString zipCode() const;
    void setZipCode(const QString &zipCode);

    QString ic() const;
    void setIc(const QString &ic);

    QString dic() const;
    void setDic(const QString &dic);

private:
    friend class odb::access;
#pragma db id auto
    int m_id;

    QString m_name;
    QString m_ic;
    QString m_dic;
    QString m_street;
    QString m_houseNumber;
    QString m_city;
    QString m_zipCode;

    // ComboItem interface
public:
    bool eq(ComboItem *other);
    QString toString();
};

#endif // CLIENT_H
