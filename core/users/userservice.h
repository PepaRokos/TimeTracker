#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "service.h"
#include "../data/core-data.h"
#include "../core_global.h"

class CORESHARED_EXPORT UserService : public Service<User>
{
public:
    UserService();
    ~UserService();

    void updateUser(QSharedPointer<User> user);
};

#endif // USERSERVICE_H
