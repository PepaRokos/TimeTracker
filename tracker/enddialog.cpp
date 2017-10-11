#include "enddialog.h"
#include "ui_enddialog.h"

#include <QMessageBox>

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

void EndDialog::setRefDateTime(const QDateTime &start)
{
    m_refDateTime = start;
}

void EndDialog::accept()
{
    if (m_refDateTime < ui->end->dateTime())
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::warning(this, tr("Date is not valid"), tr("End of task must be after start."));
    }
}
