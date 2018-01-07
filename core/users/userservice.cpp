#include "userservice.h"

#include "core-odb.hxx"

UserService::UserService()
{   
}

UserService::~UserService()
{
}

void UserService::updateUser(QSharedPointer<User> user)
{
    this->update(user);
}
