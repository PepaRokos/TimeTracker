#ifndef SETTINGSSERVICE_H
#define SETTINGSSERVICE_H

#include <QString>
#include <QSharedPointer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMetaProperty>

#include <QDecDouble.hh>
#include <QDebug>

#include "data/system.h"
#include "service.h"
#include "core_global.h"

class CORESHARED_EXPORT SettingsService : public IService
{
public:
    explicit SettingsService(QObject *parent = NULL);
    SettingsService(const QString &pluginId, QObject *parent = NULL);


    template <class T>
    QSharedPointer<T> loadSettings() {
        QSharedPointer<System> sys = loadSystem();
        QObject *objSettings = new T();
        QSharedPointer<T> settingsObj((T*)objSettings);

        if (sys.isNull())
        {
            return settingsObj;
        }

        QString settingStr = sys->settings();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(settingStr.toUtf8());
        QJsonValue val = jsonDoc.object()["Settings"];

        if (!val.isObject())
        {
            return settingsObj;
        }

        for (int i = 0; i < objSettings->metaObject()->propertyCount(); i++)
        {
            const char *propName = objSettings->metaObject()->property(i).name();             
            QJsonValue v = val.toObject()[propName];
            QVariant varVal = v.toVariant();

            if (objSettings->property(propName).canConvert<QDecDouble>())
            {
                QDecDouble dec(TO_DEC(varVal.toInt()));
                varVal = QVariant::fromValue(dec);
                objSettings->setProperty(propName, varVal);
                continue;
            }

            // all other numbers are int
            if (varVal.toInt() > 0)
            {
                objSettings->setProperty(propName, varVal.toInt());
            }
            else
            {
                objSettings->setProperty(propName, varVal);
            }
        }

        return settingsObj;
    }

    template <class T>
    void saveSettings(QSharedPointer<T> objSettings)
    {
        QObject *objSettingsQo = objSettings.data();
        QJsonDocument jsonDoc;
        QJsonObject jsonObj;

        for (int i = 0; i < objSettingsQo->metaObject()->propertyCount(); i++)
        {
            const char *propName = objSettings->metaObject()->property(i).name();
            QVariant val = objSettingsQo->property(propName);
            if (val.canConvert<QDecDouble>())
            {
                int vat = FROM_DEC(val.value<QDecDouble>());
                val = QVariant::fromValue(vat);
            }

            jsonObj[propName] = QJsonValue::fromVariant(val);
        }

        QJsonObject jsonSettings;
        jsonSettings["Settings"] = jsonObj;
        jsonDoc.setObject(jsonSettings);

        saveSystem(jsonDoc);
    }

private:
    QString m_pluginId;
    QSharedPointer<QObject> m_settings;
    QSharedPointer<System> loadSystem();
    void saveSystem(const QJsonDocument &doc);
};

#endif // SETTINGSSERVICE_H
