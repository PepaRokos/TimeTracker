#ifndef ROLESTABLEMODEL_H
#define ROLESTABLEMODEL_H

#include "autotablemodel.h"
#include "data/core-data.h"

class RolesTableModel : public AutoTableModel<Role>
{
    Q_OBJECT
public:
    explicit RolesTableModel(QObject *parent = NULL);
};

#endif // ROLESTABLEMODEL_H
