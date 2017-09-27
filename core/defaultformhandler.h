#ifndef DEFAULTFORMHANDLER_H
#define DEFAULTFORMHANDLER_H

#include "formdialog.h"
#include "iform.h"

#include "core_global.h"

class CORESHARED_EXPORT IFormHandler
{
public:
    IFormHandler() {}
    virtual ~IFormHandler() {}

    virtual void showForm(IForm *formWidget) = 0;
};

class CORESHARED_EXPORT DefaultFormHandler : public IFormHandler
{
public:
    DefaultFormHandler();
    virtual ~DefaultFormHandler();

private:
    FormDialog *m_dialog;

    // IFormHandler interface
public:
    void showForm(IForm *formWidget) override;
};

#endif // DEFAULTFORMHANDLER_H
