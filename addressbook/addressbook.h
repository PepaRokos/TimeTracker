#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "addressbook_global.h"

#include <QObject>
#include <core.h>

class ADDRESSBOOKSHARED_EXPORT AddressBook : public QObject, IMetaDataPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "addressbook.json")
    Q_INTERFACES(IPlugin)
public:
    AddressBook();

    // IMetaDataPlugin interface
protected:
    virtual void initServiceUi() override;

    // IPlugin interface
public:
    virtual QIcon pluginIcon() override;
};

#endif // ADDRESSBOOK_H
