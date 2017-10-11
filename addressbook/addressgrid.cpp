#include "addressgrid.h"

AddressGrid::AddressGrid(QWidget *parent) :GridForm<Address>(parent)
{
    setTableModel(new AutoTableModel<Address>());
}
