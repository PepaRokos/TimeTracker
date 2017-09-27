#ifndef IMETADATAPLUGIN_H
#define IMETADATAPLUGIN_H

#include <QString>

#include "core_global.h"
#include "iplugin.h"

class CORESHARED_EXPORT IMetaDataPlugin : public IPlugin
{
public:
    IMetaDataPlugin();
    virtual ~IMetaDataPlugin();

    // IPlugin interface
public:
    virtual QString pluginName();
    virtual QString pluginId();
    virtual QString pluginDescription();
    virtual int schemaVersion();
    virtual QStringList schemas();
    virtual QStringList dependsOn();
    virtual ReportList reports();

    virtual void init(const QJsonObject &metaData);

protected:
    virtual void initServiceUi() = 0;
    virtual void parseMetaData(const QJsonObject &metaData);

private:
    QString m_name;
    QString m_id;
    QString m_description;
    int m_schemaVersion;
    QStringList m_schemas;
    QStringList m_dependsOn;
    ReportList m_reports;

    QString parseLocaleText(const QJsonObject &object);
};

#endif // IMETADATAPLUGIN_H
