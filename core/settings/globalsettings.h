#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>
#include <QString>
#include <QDecDouble.hh>
#include "../core_global.h"

class CORESHARED_EXPORT GlobalSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString firmName READ firmName WRITE setFirmName)
    Q_PROPERTY(QString street READ street WRITE setStreet)
    Q_PROPERTY(QString houseNumber READ houseNumber WRITE setHouseNumber)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(int ic READ ic WRITE setIc)
    Q_PROPERTY(QString dic READ dic WRITE setDic)
    Q_PROPERTY(bool vatPayer READ vatPayer WRITE setVatPayer)
    Q_PROPERTY(QString logoPath READ logoPath WRITE setLogoPath)
    Q_PROPERTY(QDecDouble vatHigh READ vatHigh WRITE setVatHigh)
    Q_PROPERTY(QDecDouble vatFirstLower READ vatFirstLower WRITE setVatFirstLower)
    Q_PROPERTY(QDecDouble vatSecondLower READ vatSecondLower WRITE setVatSecondLower)
    Q_PROPERTY(QString email READ email WRITE setEmail)
    Q_PROPERTY(QString web READ web WRITE setWeb)
    Q_PROPERTY(QString phone READ phone WRITE setPhone)

public:
    explicit GlobalSettings(QObject *parent = 0);

    QString firmName() const;
    void setFirmName(const QString &firmName);

    QString street() const;
    void setStreet(const QString &street);

    QString houseNumber() const;
    void setHouseNumber(const QString &houseNumber);

    QString zipCode() const;
    void setZipCode(const QString &zipCode);

    QString city() const;
    void setCity(const QString &city);

    int ic() const;
    void setIc(int ic);

    QString dic() const;
    void setDic(const QString &dic);

    bool vatPayer() const;
    void setVatPayer(bool vatPayer);

    QString logoPath() const;
    void setLogoPath(const QString &logoPath);

    QDecDouble vatHigh() const;
    void setVatHigh(QDecDouble vatHigh);

    QDecDouble vatFirstLower() const;
    void setVatFirstLower(QDecDouble vatFirstLower);

    QDecDouble vatSecondLower() const;
    void setVatSecondLower(QDecDouble vatSecondLower);

    QString email() const;
    void setEmail(const QString &email);

    QString web() const;
    void setWeb(const QString &web);

    QString phone() const;
    void setPhone(const QString &phone);

private:
    QString m_firmName;
    QString m_street;
    QString m_houseNumber;
    QString m_zipCode;
    QString m_city;
    int m_ic;
    QString m_dic;
    bool m_vatPayer;
    QString m_logoPath;
    int m_vatHigh;
    int m_vatFirstLower;
    int m_vatSecondLower;
    QString m_email;
    QString m_web;
    QString m_phone;

signals:

public slots:
};

typedef QSharedPointer<GlobalSettings> GlobalSettingsPtr;

#endif // GLOBALSETTINGS_H
