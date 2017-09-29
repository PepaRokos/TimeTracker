#include "trackerform.h"
#include "ui_trackerform.h"

#include "clientdialog.h"

#include <emptystringvalidator.h>

TrackerForm::TrackerForm(QWidget *parent) :
    AutoForm<Project>(parent),
    ui(new Ui::TrackerForm)
{
    ui->setupUi(this);

    registerBinding(ui->name);
    registerBinding(ui->start);
    registerBinding(ui->dueTo);
    registerBinding(ui->pricePerHour);

    DateValidator *dateValidator = new DateValidator(ui->dueTo, tr("Due to date must be after start date."), ui->start);
    registerValidator(dateValidator);
    EmptyStringValidator *nameValidator = new EmptyStringValidator(ui->name, tr("Project name cannot by empty."));
    registerValidator(nameValidator);
}

TrackerForm::~TrackerForm()
{
    delete ui;
}

void TrackerForm::registerCombos()
{
    Service<Client> srv;
    registerBinding(ui->client, ComboData::createComboData(srv.all()));
}

void TrackerForm::on_btnNewClient_clicked()
{
    ClientDialog *dlg = new ClientDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    connect(dlg, &QDialog::accepted, [this, dlg](){
        Service<Client> srv;
        srv.save(dlg->client());

        registerBinding(ui->client, ComboData::createComboData(srv.all()));
        bindToUi();
    });
}

DateValidator::DateValidator(QWidget *widget, const QString &message, QDateTimeEdit *startEdit)
    :IValidator(widget, message)
{
    m_startEdit = startEdit;
}

bool DateValidator::validate()
{
    QDateTimeEdit *endEdit = qobject_cast<QDateTimeEdit*>(m_widget);
    Q_ASSERT(endEdit != NULL);

    return m_startEdit->dateTime() < endEdit->dateTime();
}
