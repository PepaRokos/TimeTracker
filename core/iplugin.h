#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QString>
#include <QWidget>
#include <QtPlugin>
#include <QJsonObject>
#include <QStringList>
#include <QIcon>
#include <QTranslator>
#include <QMessageBox>

#include "service.h"
#include "igridform.h"
#include "reporting/report.h"

class IPlugin
{

public:
    IPlugin() {
        m_ui = NULL;
        m_service = NULL;
        m_settingsUi = NULL;
    }

    virtual ~IPlugin() {
        if (m_service != NULL)
        {
            delete m_service;
        }

        if (m_ui != NULL && m_ui->parent() == NULL)
        {
            delete m_ui;
        }

        if (m_settingsUi != NULL && m_settingsUi->parent() == NULL)
        {
            delete m_settingsUi;
        }
    }

    virtual QString pluginName() = 0;
    virtual QString pluginId() = 0;
    virtual QString pluginDescription() = 0;
    virtual int schemaVersion() = 0;
    virtual QStringList schemas() = 0;
    virtual QStringList dependsOn() = 0;
    virtual ReportList reports() = 0;

    virtual void init(const QJsonObject &metaData) = 0;

    virtual QWidget *ui() {
        PermissionEvaluator permEv;
        if (!permEv.hasPermission(pluginId(), PERM_READ))
        {
            QMessageBox::critical(m_ui, QObject::tr("Permission denied"), QObject::tr("You don't have permission to open this plugin."));
            return NULL;
        }

        IGridForm *form = qobject_cast<IGridForm*>(m_ui);
        bool filled = true;

        if (form != NULL)
        {
            filled = form->fillData();
        }

        return filled ? m_ui : NULL;
    }

    virtual QWidget *settingsUi() {
        return m_settingsUi;
    }

    virtual QString settingsTabLabel() {
        return pluginName();
    }

    template<class T>
    Service<T> *service() {
        return (Service<T>*)m_service;
    }

    virtual bool showIcon() { return true; }
    virtual QTranslator* translator() { return NULL; }
    virtual QIcon pluginIcon() { return QIcon(); }
    QMap<QString, QString> translations() { return m_translations; }

    virtual bool hasNumberSeries() { return false; }
    virtual QString numberSeriesPrefix() { return ""; }

protected:
    QTranslator* translatorFrom(QString fileName) {
        QTranslator *trans = new QTranslator();
        trans->load(fileName + QLocale::system().name());

        return trans;
    }

    QWidget *m_ui;
    QWidget *m_settingsUi;
    IService *m_service;
    QMap<QString, QString> m_translations;
};

#define PluginInterface_iid "cz.itsolved.prodejna.IPlugin"

Q_DECLARE_INTERFACE(IPlugin, PluginInterface_iid)

#endif // IPLUGIN_H
