#ifndef ADDRESSGRID_H
#define ADDRESSGRID_H

#include <core.h>

#include "data/address.h"
#include "addressbook-odb.hxx"

class AddressGrid : public GridForm<Address>
{
    Q_OBJECT
public:
    explicit AddressGrid(QWidget *parent = Q_NULLPTR);
};

#endif // ADDRESSGRID_H
