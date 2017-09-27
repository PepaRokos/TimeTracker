#include "project.h"
#include <define.h>

Project::Project(QObject *parent) : QObject(parent)
{
    m_active = true;
    m_pricePerHour = 0;
    m_totalPrice = 0;

    m_start = QDateTime::currentDateTime();
    m_dueTo = QDateTime::currentDateTime();
}

QString Project::name() const
{
    return m_name;
}

void Project::setName(const QString &name)
{
    m_name = name;
}

int Project::id() const
{
    return m_id;
}

void Project::setId(int id)
{
    m_id = id;
}

QSharedPointer<QObject> Project::client() const
{
    return m_client;
}

void Project::setClient(const QSharedPointer<QObject> &client)
{
    if (qobject_cast<Client*>(client.data()) != nullptr)
    {
        m_client = qSharedPointerCast<Client, QObject>(client);
    }
}

QDateTime Project::start() const
{
    return m_start;
}

void Project::setStart(const QDateTime &start)
{
    m_start = start;
}

QDateTime Project::dueTo() const
{
    return m_dueTo;
}

void Project::setDueTo(const QDateTime &dueTo)
{
    m_dueTo = dueTo;
}

QDateTime Project::end() const
{
    return m_end;
}

void Project::setEnd(const QDateTime &end)
{
    m_end = end;
}

QOdbList<TimeLogPtr> Project::timeLog() const
{
    return m_timeLog;
}

void Project::setTimeLog(const QOdbList<TimeLogPtr> &timeLog)
{
    m_timeLog = timeLog;
}

void Project::addTimeLog(TimeLogPtr log)
{
    m_timeLog.append(log);
}

void Project::removeLastLog()
{
    m_timeLog.removeLast();
}

bool Project::active() const
{
    return m_active;
}

void Project::setActive(bool active)
{
    m_active = active;
}

QDecDouble Project::pricePerHour() const
{
    return TO_DEC(m_pricePerHour);
}

void Project::setPricePerHour(QDecDouble pricePerHour)
{
    m_pricePerHour = FROM_DEC(pricePerHour);
}

QDecDouble Project::totalPrice() const
{
    return TO_DEC(m_totalPrice);
}

void Project::setTotalPrice(QDecDouble totalPrice)
{
    m_totalPrice = FROM_DEC(totalPrice);
}

QTime Project::totalTime() const
{
    return m_totalTime;
}

void Project::setTotalTime(const QTime &totalTime)
{
    m_totalTime = totalTime;
}
