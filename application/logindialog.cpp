#include "logindialog.h"
#include "ui_logindialog.h"
#include "../core/core.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::login() const
{
    return ui->editLogin->text();
}

QString LoginDialog::password() const
{
    return ui->editPassword->text();
}

void LoginDialog::reset()
{
    ui->editLogin->setText("");
    ui->editPassword->setText("");
}

void LoginDialog::accept()
{
    PermissionService srv;
    if (srv.checkLogin(ui->editLogin->text(), ui->editPassword->text()))
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::critical(this, "Bad login", "Bad login or password");
    }
}
