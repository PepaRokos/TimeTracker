#include "enddialog.h"
#include "ui_enddialog.h"

EndDialog::EndDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndDialog)
{
    ui->setupUi(this);

    ui->end->setDateTime(QDateTime::currentDateTime());
}

EndDialog::~EndDialog()
{
    delete ui;
}

QDateTime EndDialog::end()
{
    return ui->end->dateTime();
}
