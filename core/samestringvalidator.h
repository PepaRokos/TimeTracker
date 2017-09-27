#ifndef SAMESTRINGVALIDATOR_H
#define SAMESTRINGVALIDATOR_H
#include "ivalidator.h"
#include "core_global.h"

class CORESHARED_EXPORT SameStringValidator : public IValidator
{
public:
    SameStringValidator(QWidget * widget_1, QWidget *widget_2, const QString &errorMessage);
    bool validate();
private:
QWidget * m_widget_2;
};

#endif // SAMESTRINGVALIDATOR_H
