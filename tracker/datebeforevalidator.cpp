#include "datebeforevalidator.h"

DateBeforeValidator::DateBeforeValidator(QWidget *widget, const QString &message, QDateTimeEdit *startEdit)
    :IValidator(widget, message)
{
    m_startEdit = startEdit;
}

DateBeforeValidator::DateBeforeValidator(QWidget *widget, const QString &message, const QDateTime &startdateTime)
    :IValidator(widget, message)
{
    m_startDateTime = startdateTime;
    m_startEdit = Q_NULLPTR;
}

bool DateBeforeValidator::validate()
{
    QDateTime start;

    if (m_startEdit != Q_NULLPTR)
    {
        QDateTimeEdit *startEdit = qobject_cast<QDateTimeEdit*>(m_startEdit);
        Q_ASSERT(startEdit != Q_NULLPTR);

        start = startEdit->dateTime();
    }
    else
    {
        start = m_startDateTime;
    }

    QDateTimeEdit *endEdit = qobject_cast<QDateTimeEdit*>(m_widget);
    Q_ASSERT(endEdit != Q_NULLPTR);

    return start < endEdit->dateTime();
}
