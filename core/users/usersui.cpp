#include "usersui.h"
#include "tablemodel.h"

UsersUi::UsersUi(QWidget *parent) :GridForm<User>(parent)
{
    setTableModel(new UsersTableModel);
}

UsersUi::~UsersUi()
{

}
