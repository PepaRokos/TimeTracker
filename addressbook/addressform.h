#ifndef ADDRESSFORM_H
#define ADDRESSFORM_H

#include <QWidget>
#include <core.h>

#include "data/address.h"
#include "addressbook-odb.hxx"

namespace Ui {
class AddressForm;
}

class AddressForm : public AutoForm<Address>
{
    Q_OBJECT

public:
    explicit AddressForm(QWidget *parent = 0);
    ~AddressForm();

private:
    Ui::AddressForm *ui;
};

#endif // ADDRESSFORM_H
