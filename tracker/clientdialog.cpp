#include "clientdialog.h"
#include "ui_clientdialog.h"

ClientDialog::ClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientDialog)
{
    ui->setupUi(this);

    m_client = ClientPtr(new Client());

    m_binder.registerBinding(ui->name);
    m_binder.registerBinding(ui->ic);
    m_binder.registerBinding(ui->dic);
    m_binder.registerBinding(ui->street);
    m_binder.registerBinding(ui->houseNumber);
    m_binder.registerBinding(ui->zipCode);
    m_binder.registerBinding(ui->city);

    m_binder.setData(m_client.data());
    m_binder.bindToUi();
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

ClientPtr ClientDialog::client()
{
    return m_client;
}

void ClientDialog::accept()
{
    m_binder.bindToData();
    QDialog::accept();
}
