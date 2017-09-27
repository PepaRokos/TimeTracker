#ifndef SYSTEM_H
#define SYSTEM_H

#include "core_global.h"
#include <QString>

#include <odb/core.hxx>

#pragma db object
class CORESHARED_EXPORT System
{
public:
    System();
    virtual ~System();

    int id() const;
    void setId(int id);

    QString pluginId() const;

    QString schemaVersion() const;

    QString settings() const;
    void setSettings(const QString &settings);

private:
    friend class odb::access;

#pragma db id auto
    int m_id;
    QString m_pluginId;
    QString m_schemaVersion;
    QString m_settings;
};

#endif // SYSTEM_H
