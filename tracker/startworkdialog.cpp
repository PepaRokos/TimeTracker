#include "startworkdialog.h"
#include "ui_startworkdialog.h"

StartWorkDialog::StartWorkDialog(QDecDouble pricePerHour, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWorkDialog)
{
    ui->setupUi(this);
    m_timeLog = TimeLogPtr(new TimeLog());
    m_timeLog->setPricePerHour(pricePerHour);

    m_binder.registerBinding(ui->description);
    m_binder.registerBinding(ui->pricePerHour);
    m_binder.registerBinding(ui->start);

    m_binder.setData(m_timeLog.data());
    m_binder.bindToUi();
}

StartWorkDialog::~StartWorkDialog()
{
    delete ui;
}

TimeLogPtr StartWorkDialog::log()
{
    return m_timeLog;
}

void StartWorkDialog::accept()
{
    m_binder.bindToData();
    QDialog::accept();
}
