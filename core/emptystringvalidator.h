#ifndef EMPTYSTRINGVALIDATOR_H
#define EMPTYSTRINGVALIDATOR_H

#include <QString>
#include "ivalidator.h"

#include "core_global.h"

class CORESHARED_EXPORT EmptyStringValidator : public IValidator
{
public:
    EmptyStringValidator(QWidget *widget, const QString &errMessage);

    // IValidator interface
public:
    bool validate();
};

#endif // EMPTYSTRINGVALIDATOR_H
