#ifndef ROLES_H
#define ROLES_H

#include "imetadataplugin.h"

class Roles : public IMetaDataPlugin
{
public:
    Roles();

    // IMetaDataPlugin interface
protected:
    void initServiceUi();

    // IPlugin interface
public:
    virtual QIcon pluginIcon();
};

#endif // ROLES_H
