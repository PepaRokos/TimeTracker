#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "autotablemodel.h"
#include "../data/core-data.h"
#include "core-odb.hxx"

class UsersTableModel : public AutoTableModel<User>
{
    Q_OBJECT
public:
    explicit UsersTableModel(QObject *parent = NULL);
};

#endif // TABLEMODEL_H
