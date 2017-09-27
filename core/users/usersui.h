#ifndef USERSUI_H
#define USERSUI_H

#include "gridform.h"
#include "../data/core-data.h"
#include "core-odb.hxx"

class UsersUi : public GridForm<User>
{
    Q_OBJECT

public:
    explicit UsersUi(QWidget *parent = NULL);
    ~UsersUi();
};

#endif // USERSUI_H
