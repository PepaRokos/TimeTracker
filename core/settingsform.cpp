#include "settingsform.h"
#include "ui_settingsform.h"

#include "settingsservice.h"
#include "context.h"
#include "iplugin.h"
#include "iform.h"

#include <QMessageBox>

SettingsForm::SettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    foreach (IPlugin *plugin, Context::instance().plugins()) {
        if (plugin->settingsUi() != NULL)
        {
            SettingsService srv(plugin->pluginId());
            IForm *tab = qobject_cast<IForm*>(plugin->settingsUi());

            if (tab != NULL)
            {
                tab->loadEntity();
                ui->tabWidget->addTab(tab, QIcon(), plugin->settingsTabLabel());
            }
        }
    }
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::on_buttonBox_accepted()
{
    accept();
}

void SettingsForm::accept()
{
    if (!Context::instance().currentUser()->isAdmin())
    {
        QMessageBox::critical(this, tr("Permission denied"), tr("You don't have permission to save settings."));
        return;
    }

    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        IForm *tab = qobject_cast<IForm*>(ui->tabWidget->widget(i));
        if (tab != NULL)
        {
            tab->saveRecord();
        }
    }
    QDialog::accept();
}

void SettingsForm::on_buttonBox_rejected()
{
    reject();
}
