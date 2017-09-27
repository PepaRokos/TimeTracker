#include "coreplugin.h"
#include <QJsonDocument>
#include <QFile>
#include <QApplication>

#include "settings/globalsettingsform.h"

CorePlugin::CorePlugin()
{
    Q_INIT_RESOURCE(rc);

    QFile f(":/metaData.json");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    init(d.object());
    f.close();
}

CorePlugin::~CorePlugin()
{
}

void CorePlugin::initServiceUi()
{
    m_service = NULL;
    m_ui = NULL;
    m_settingsUi = new GlobalSettingsForm();
}

QTranslator *CorePlugin::translator()
{
    return translatorFrom(":/translations/core_");
}

