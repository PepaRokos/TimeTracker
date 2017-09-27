#include "timelog.h"
#include <define.h>

TimeLog::TimeLog(QObject *parent) :QObject(parent)
{
    m_minutes = 0;
    m_pricePerHour = 0;
    m_price = 0;

    m_start = QDateTime::currentDateTime();
    //m_end.
}

int TimeLog::id() const
{
    return m_id;
}

void TimeLog::setId(int id)
{
    m_id = id;
}

QWeakPointer<Project> TimeLog::project() const
{
    return m_project;
}

void TimeLog::setProject(const QWeakPointer<Project> &project)
{
    m_project = project;
}

QString TimeLog::description() const
{
    return m_description;
}

void TimeLog::setDescription(const QString &description)
{
    m_description = description;
}

QDateTime TimeLog::start() const
{
    return m_start;
}

void TimeLog::setStart(const QDateTime &start)
{
    m_start = start;
}

QDateTime TimeLog::end() const
{
    return m_end;
}

void TimeLog::setEnd(const QDateTime &end)
{
    m_end = end;
}

int TimeLog::minutes() const
{
    return m_minutes;
}

void TimeLog::setMinutes(int minutes)
{
    m_minutes = minutes;
}

QDecDouble TimeLog::price() const
{
    return TO_DEC(m_price);
}

void TimeLog::setPrice(QDecDouble price)
{
    m_price = FROM_DEC(price);
}

QDecDouble TimeLog::pricePerHour() const
{
    return TO_DEC(m_pricePerHour);
}

void TimeLog::setPricePerHour(QDecDouble pricePerHour)
{
    m_pricePerHour = FROM_DEC(pricePerHour);
}
