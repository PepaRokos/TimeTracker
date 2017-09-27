#include "emptystringvalidator.h"

#include <QMetaObject>
#include <QMetaProperty>

EmptyStringValidator::EmptyStringValidator(QWidget *widget, const QString &errMessage)
    :IValidator(widget, errMessage)
{   
}

bool EmptyStringValidator::validate()
{
    QString data = m_widget->property(m_widget->metaObject()->userProperty().name()).toString();
    if (data.isEmpty())
    {
        m_widget->setFocus();
        return false;
    }

    return true;
}

