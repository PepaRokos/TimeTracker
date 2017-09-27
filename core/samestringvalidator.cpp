#include "samestringvalidator.h"
#include <QMetaProperty>

SameStringValidator::SameStringValidator(QWidget *widget_1, QWidget * widget_2, const QString & errorMessage)
    :IValidator(widget_1,errorMessage)
{
    m_widget_2 = widget_2;
}

bool SameStringValidator::validate()
{
    QString data = m_widget->property(m_widget->metaObject()->userProperty().name()).toString();
    QString data_2 = m_widget_2->property(m_widget_2->metaObject()->userProperty().name()).toString();
    if (data != data_2)
    {
        m_widget->setFocus();
        return false;
    }

    return true;
}
