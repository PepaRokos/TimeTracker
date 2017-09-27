#ifndef TIMELOG_H
#define TIMELOG_H

#include "tracker-data.h"

#include <QObject>
#include <QDateTime>
#include <QWeakPointer>
#include <odb/core.hxx>

#include <QDecDouble.hh>

#pragma db object
class TimeLog : public QObject
{
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QDateTime start READ start WRITE setStart)
    Q_PROPERTY(QDateTime end READ end WRITE setEnd)
    Q_PROPERTY(int minutes READ minutes WRITE setMinutes)
    Q_PROPERTY(QDecDouble pricePerHour READ pricePerHour WRITE setPricePerHour)
    Q_PROPERTY(QDecDouble price READ price WRITE setPrice)

    Q_OBJECT
public:
    explicit TimeLog(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QWeakPointer<Project> project() const;
    void setProject(const QWeakPointer<Project> &project);

    QString description() const;
    void setDescription(const QString &description);

    QDateTime start() const;
    void setStart(const QDateTime &start);

    QDateTime end() const;
    void setEnd(const QDateTime &end);

    int minutes() const;
    void setMinutes(int minutes);

    QDecDouble price() const;
    void setPrice(QDecDouble price);

    QDecDouble pricePerHour() const;
    void setPricePerHour(QDecDouble pricePerHour);

private:
    friend class odb::access;
#pragma db id auto
    int m_id;

#pragma db not_null
    QWeakPointer<Project> m_project;
    QString m_description;
    QDateTime m_start;
    QDateTime m_end;
    int m_minutes;
    int m_pricePerHour;
    int m_price;
};

#endif // TIMELOG_H
