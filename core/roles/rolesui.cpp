#include "rolesui.h"
#include "rolestablemodel.h"

RolesUi::RolesUi(QWidget *parent)
    :GridForm<Role>(parent)
{
    setTableModel(new RolesTableModel());
}

RolesUi::~RolesUi()
{
}
