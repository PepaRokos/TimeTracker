#ifndef TRACKER_H
#define TRACKER_H

#include "tracker_global.h"
#include <core.h>

class TRACKERSHARED_EXPORT Tracker : public QObject, IMetaDataPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "tracker.json")
    Q_INTERFACES(IPlugin)

public:
    Tracker();

protected:
    void initServiceUi() Q_DECL_OVERRIDE;

    // IPlugin interface
public:
    virtual QIcon pluginIcon();
    //QTranslator *translator();
};

#endif // TRACKER_H
