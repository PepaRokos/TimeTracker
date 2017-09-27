#ifndef SEASON_H
#define SEASON_H

#include "core_global.h"

#include <QObject>
#include <QString>
#include <QDate>

#include <odb/core.hxx>

#pragma db object
class CORESHARED_EXPORT Season : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QDate validFrom READ validFrom WRITE setValidFrom)
    Q_PROPERTY(QDate validTo READ validTo WRITE setValidTo)
    Q_PROPERTY(bool active READ active WRITE setActive)
public:
    explicit Season(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QDate validFrom() const;
    void setValidFrom(const QDate &validFrom);

    QDate validTo() const;
    void setValidTo(const QDate &validTo);

    bool active() const;
    void setActive(bool active);

    int id() const;
    void setId(int id);

private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_name;
    QDate m_validFrom;
    QDate m_validTo;
    bool m_active;
};

typedef QSharedPointer<Season> SeasonPtr;

#endif // SEASON_H
