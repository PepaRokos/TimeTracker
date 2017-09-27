#include "trackerform.h"
#include "ui_trackerform.h"

#include "clientdialog.h"

TrackerForm::TrackerForm(QWidget *parent) :
    AutoForm<Project>(parent),
    ui(new Ui::TrackerForm)
{
    ui->setupUi(this);

    registerBinding(ui->name);
    registerBinding(ui->start);
    registerBinding(ui->dueTo);
    registerBinding(ui->pricePerHour);
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
