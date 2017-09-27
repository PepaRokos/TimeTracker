#ifndef ROLESUI_H
#define ROLESUI_H

#include "gridform.h"
#include "data/core-data.h"
#include "core-odb.hxx"

class RolesUi : public GridForm<Role>
{
    Q_OBJECT
public:
    explicit RolesUi(QWidget *parent = NULL);
    ~RolesUi();
};

#endif // ROLESUI_H
