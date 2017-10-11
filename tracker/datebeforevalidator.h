#ifndef DATEBEFOREVALIDATOR_H
#define DATEBEFOREVALIDATOR_H

#include <core.h>
#include <QWidget>
#include <QDateTimeEdit>
#include <QDateTime>

class DateBeforeValidator : public IValidator
{
public:
    DateBeforeValidator(QWidget *widget, const QString &message, QDateTimeEdit *startEdit);
    DateBeforeValidator(QWidget *widget, const QString &message, const QDateTime &startdateTime);

    // IValidator interface
public:
    virtual bool validate() override;

private:
    QDateTimeEdit *m_startEdit;
    QDateTime m_startDateTime;
};

#endif // DATEBEFOREVALIDATOR_H
