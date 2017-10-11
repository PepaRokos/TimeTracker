#include "startworkdialog.h"
#include "ui_startworkdialog.h"

#include <emptystringvalidator.h>
#include "datebeforevalidator.h"

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

    IValidator *descValidator = new EmptyStringValidator(ui->description, tr("Description cannot by empty."));
    m_binder.registerValidator(descValidator);

    m_binder.setData(m_timeLog.data());
    m_binder.bindToUi();

    connect(&m_binder, &ObjectBinder::validationError, [this](QString message){
       QMessageBox::warning(this, tr("Data not valid"), message);
    });
}

StartWorkDialog::~StartWorkDialog()
{
    delete ui;
}

TimeLogPtr StartWorkDialog::log()
{
    return m_timeLog;
}

void StartWorkDialog::setRefDateTime(const QDateTime &dateTime)
{
    m_refDateTime = dateTime;

    if (dateTime.isValid())
    {
        IValidator *dateValidator = new DateBeforeValidator(ui->start, tr("Start time must be after end of last task."), dateTime);
        m_binder.registerValidator(dateValidator);
    }
}

void StartWorkDialog::accept()
{
    if (m_binder.bindToData())
    {
        QDialog::accept();
    }
}
