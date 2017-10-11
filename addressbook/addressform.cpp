#include "addressform.h"
#include "ui_addressform.h"

AddressForm::AddressForm(QWidget *parent) :
    AutoForm<Address>(parent),
    ui(new Ui::AddressForm)
{
    ui->setupUi(this);

    registerBinding(ui->company);
    registerBinding(ui->ic);
    registerBinding(ui->dic);
    registerBinding(ui->contactName);
    registerBinding(ui->street);
    registerBinding(ui->houseNumber);
    registerBinding(ui->city);
    registerBinding(ui->zipCode);
    registerBinding(ui->web);
    registerBinding(ui->email);
    registerBinding(ui->note);
}

AddressForm::~AddressForm()
{
    delete ui;
}
