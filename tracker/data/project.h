#ifndef PROJECT_H
#define PROJECT_H

#include "tracker-data.h"

#include <QObject>
#include <QDateTime>
#include <QString>

#include <odb/core.hxx>
#include <odb/qt/list.hxx>

#include <QDecDouble.hh>

#pragma db object
class Project : public QObject
{
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QSharedPointer<QObject> client READ client WRITE setClient)
    Q_PROPERTY(QDateTime start READ start WRITE setStart)
    Q_PROPERTY(QDateTime dueTo READ dueTo WRITE setDueTo)
    Q_PROPERTY(QDateTime end READ end WRITE setEnd)
    Q_PROPERTY(QTime totalTime READ totalTime WRITE setTotalTime)
    Q_PROPERTY(QDecDouble pricePerHour READ pricePerHour WRITE setPricePerHour)
    Q_PROPERTY(QDecDouble totalPrice READ totalPrice WRITE setTotalPrice)
    Q_PROPERTY(bool active READ active WRITE setActive)

    Q_OBJECT
public:
    explicit Project(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(int id);

    QSharedPointer<QObject> client() const;
    void setClient(const QSharedPointer<QObject> &client);

    QDateTime start() const;
    void setStart(const QDateTime &start);

    QDateTime dueTo() const;
    void setDueTo(const QDateTime &dueTo);

    QDateTime end() const;
    void setEnd(const QDateTime &end);

    QOdbList<TimeLogPtr> timeLog() const;
    void setTimeLog(const QOdbList<TimeLogPtr> &timeLog);
    void addTimeLog(TimeLogPtr log);
    void removeLastLog();

    bool active() const;
    void setActive(bool active);

    QDecDouble pricePerHour() const;
    void setPricePerHour(QDecDouble pricePerHour);

    QDecDouble totalPrice() const;
    void setTotalPrice(QDecDouble totalPrice);

    QTime totalTime() const;
    void setTotalTime(const QTime &totalTime);

private:
    friend class odb::access;
#pragma db id auto
    int m_id;

    QString m_name;
    ClientPtr m_client;
    QDateTime m_start;
    QDateTime m_dueTo;
    QDateTime m_end;
    QTime m_totalTime;
    #pragma db value_not_null inverse(m_project)
    QOdbList<TimeLogPtr> m_timeLog;
    bool m_active;
    int m_pricePerHour;
    int m_totalPrice;
};

#pragma db view object(Project)
struct ProjectSum
{
    ProjectSum();

    QDecDouble totalPrice() const;
    void setTotalPrice(QDecDouble totalPrice);

    #pragma db column("count(id)")
    int m_count;
    #pragma db column("sum(totalPrice)")
    int m_totalPrice;
};

#endif // PROJECT_H
