#include "season.h"

Season::Season(QObject *parent)
    :QObject(parent)
{
    m_id = 0;
    m_active = false;
}

QString Season::name() const
{
    return m_name;
}

void Season::setName(const QString &name)
{
    m_name = name;
}

QDate Season::validFrom() const
{
    return m_validFrom;
}

void Season::setValidFrom(const QDate &validFrom)
{
    m_validFrom = validFrom;
}

QDate Season::validTo() const
{
    return m_validTo;
}

void Season::setValidTo(const QDate &validTo)
{
    m_validTo = validTo;
}

bool Season::active() const
{
    return m_active;
}

void Season::setActive(bool active)
{
    m_active = active;
}

int Season::id() const
{
    return m_id;
}

void Season::setId(int id)
{
    m_id = id;
}
