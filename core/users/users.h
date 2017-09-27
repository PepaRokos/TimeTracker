#ifndef USERS_H
#define USERS_H
#include "imetadataplugin.h"
#include "userform.h"
#include "usersui.h"

class Users : public IMetaDataPlugin
{
public:
    Users();

    // IMetaDataPlugin interface
protected:
    void initServiceUi();

    // IPlugin interface
public:
    virtual QIcon pluginIcon();
};

#endif // USERS_H
