#include "imetadataplugin.h"

#include <QJsonValue>
#include <QJsonArray>
#include <QLocale>
#include <QDebug>
#include <QApplication>

#include "igridform.h"

IMetaDataPlugin::IMetaDataPlugin()
{
    m_service = NULL;
    m_ui = NULL;
}

IMetaDataPlugin::~IMetaDataPlugin()
{
}

QString IMetaDataPlugin::pluginName()
{
    return m_name;
}

QString IMetaDataPlugin::pluginId()
{
    return m_id;
}

QString IMetaDataPlugin::pluginDescription()
{
    return m_description;
}

int IMetaDataPlugin::schemaVersion()
{
    return m_schemaVersion;
}

QStringList IMetaDataPlugin::schemas()
{
    return m_schemas;
}

QStringList IMetaDataPlugin::dependsOn()
{
    return m_dependsOn;
}

ReportList IMetaDataPlugin::reports()
{
    return m_reports;
}

void IMetaDataPlugin::init(const QJsonObject &metaData)
{
    parseMetaData(metaData);

    qApp->installTranslator(this->translator());

    initServiceUi();

    if (IGridForm *pluginUi = dynamic_cast<IGridForm*>(m_ui))
    {
        pluginUi->setPluginId(pluginId());
        pluginUi->setTranslations(m_translations);
    }

    if (m_service != NULL)
    {
        m_service->setPluginId(pluginId());
    }
}

void IMetaDataPlugin::parseMetaData(const QJsonObject &metaData)
{
#ifdef _DEBUG
    qDebug() << metaData;
#endif

    QJsonValue data = metaData["MetaData"];
    if (!data.isObject()) {
        return;
    }

    m_name = parseLocaleText(data.toObject()["name"].toObject());
    m_description = parseLocaleText(data.toObject()["description"].toObject());
    m_id = data.toObject()["id"].toString();
    m_schemaVersion = data.toObject()["schemaVersion"].toInt();

    foreach (QJsonValue schVal, data.toObject()["sql"].toArray()) {
        m_schemas.append(schVal.toString());
    }

    foreach (QJsonValue depVal, data.toObject()["dependecies"].toArray()) {
        m_dependsOn.append(depVal.toString());
    }

    QJsonValue trVal = data.toObject()["translations"];
    QString locale = QLocale::system().name();
    QJsonValue trLocalized;
    foreach (QString key, trVal.toObject().keys()) {
        if (locale.contains(key, Qt::CaseInsensitive)) {
            trLocalized = trVal.toObject()[key];
            break;
        }
    }

    if (!trLocalized.isNull())
    {
        foreach (QString key, trLocalized.toObject().keys()) {
            m_translations[key] = trLocalized.toObject()[key].toString();
        }
    }

    QJsonValue repArray = data.toObject()["reports"];
    foreach (QJsonValue repVal, repArray.toArray()) {
        QJsonObject repObj = repVal.toObject();

        ReportPtr report = ReportPtr(new Report());
        report->setName(repObj["name"].toString());
        report->setDescription(repObj["description"].toString());
        report->setListReport(repObj["listReport"].toBool());
        report->setFile(repObj["file"].toString());

        m_reports.append(report);
    }
}

QString IMetaDataPlugin::parseLocaleText(const QJsonObject &object)
{
    QString locale = QLocale::system().name();
    QString ret;

    foreach (QString key, object.keys()) {
        if (locale.contains(key, Qt::CaseInsensitive)) {
            ret = object[key].toString();
            break;
        }
    }

    if (ret.isEmpty()) {
        ret = object["default"].toString();
    }

    return ret;
}

