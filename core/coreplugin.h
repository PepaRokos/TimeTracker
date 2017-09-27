#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include "imetadataplugin.h"

class CorePlugin : public IMetaDataPlugin
{
public:
    CorePlugin();
    ~CorePlugin();

    // IMetaDataPlugin interface
protected:
    virtual void initServiceUi();

    // IPlugin interface
public:
    QTranslator *translator() override;
};

#endif // COREPLUGIN_H
