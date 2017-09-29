#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <QWidget>
#include <QString>
#include <QSharedPointer>

#include "core_global.h"

class CORESHARED_EXPORT IValidator
{
public:
    IValidator(QWidget *widget, const QString &errMessage)
    {
        m_widget = widget;
        m_errMessage = errMessage;
    }

    virtual ~IValidator() {}

    virtual bool validate() = 0;

    QString errMessage()
    {
        return m_errMessage;
    }

protected:
    QWidget *m_widget;

private:
    QString m_errMessage;
};

typedef QSharedPointer<IValidator> IValidatorPtr;

#endif // IVALIDATOR_H

