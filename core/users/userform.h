#ifndef USERFORM_H
#define USERFORM_H

#include <QWidget>
#include "autoform.h"
#include "../data/core-data.h"
#include "core-odb.hxx"

namespace Ui {
class UserForm;
}

class UserForm : public AutoForm<User>
{
    Q_OBJECT

public:
    explicit UserForm(QWidget *parent = 0);
    ~UserForm();

private:
    Ui::UserForm *ui;
    bool m_passChanged;

    // AutoForm interface
protected:
    void bindOtherToUi();
    bool bindOtherToData();
private slots:
    void on_password_textChanged(const QString &arg1);
    void on_retypePassword_textChanged(const QString &arg1);
};

#endif // USERFORM_H
