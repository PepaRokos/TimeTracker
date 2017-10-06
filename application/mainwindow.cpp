#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core.h>

#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_lblUser = new QLabel(this);
    ui->statusBar->addWidget(m_lblUser);

    m_loginDialog = new LoginDialog(this);

    ui->tabWidget->setVisible(false);

    QFile styleFile(":/style.css");

    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(styleFile.readAll());
    }

    connect(m_loginDialog, &LoginDialog::accepted, [this]{
        PermissionService service;
        QSharedPointer<User> u = service.loadUser(m_loginDialog->login());
        Context::instance().setCurrentUser(u);

        m_lblUser->setText(u->name());
        ui->labelUser->setText(u->name());
        openDashboard();
        m_loginDialog->reset();
    });

    connect(m_loginDialog, &LoginDialog::rejected, [this]{
        close();
    });

    Context::instance().loadPlugins();
    int i = 0;

    foreach (IPlugin *plugin, Context::instance().plugins()) {
        if (plugin->pluginId() != "CORE" && plugin->showIcon())
        {
            QToolButton *plugButton = new QToolButton(this);
            plugButton->setText(plugin->pluginName());
            plugButton->setIcon(plugin->pluginIcon());
            plugButton->setIconSize(QSize(32, 32));
            plugButton->setAutoRaise(true);
            plugButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            ui->navigation->layout()->addWidget(plugButton);
            plugButton->setProperty(PLUGIN_INDEX, i);
            connect(plugButton, SIGNAL(clicked()), this, SLOT(openPlugin()) );
        }

        i++;
    }

   ((QVBoxLayout*)ui->navigation->layout())->addStretch(1);

    if (Context::instance().db() != NULL)
    {
        ui->navigation->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
    Context::instance().destroy();
}

void MainWindow::openPlugin()
{
    QVariant var = QObject::sender()->property(PLUGIN_INDEX);
    IPlugin *plugin = Context::instance().plugins().at(var.toInt());

    openPlugin(plugin);
}

void MainWindow::on_actionOpen_database_triggered()
{
    closaAllTabs();
    closeDashboard();

    QString dbFile = QFileDialog::getOpenFileName(this, "Open Database", "", "Database Files (*.db)");
    if (!dbFile.isEmpty())
    {
        Context::instance().openDb(dbFile);
        ui->navigation->setEnabled(true);
        on_actionLogin_triggered();
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);

    if (ui->tabWidget->count() == 0)
    {
        ui->dashboard->setVisible(true);
        ui->tabWidget->setVisible(false);

        refreshDashboard();
    }
}

void MainWindow::on_actionLogin_triggered()
{
    closaAllTabs();
    closeDashboard();

    QSharedPointer<User> u;
    Context::instance().setCurrentUser(u);
    m_lblUser->setText("");
    m_loginDialog->show();
}

void MainWindow::showEvent(QShowEvent *evt)
{
    QWidget::showEvent(evt);
    if (Context::instance().db() != NULL && Context::instance().currentUser().data() == NULL)
    {
        m_loginDialog->show();
    }
}

void MainWindow::closeEvent(QCloseEvent *evt)
{
    Context::instance().destroy();
    evt->accept();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsForm *settings = new SettingsForm(this);
    settings->show();
}

void MainWindow::on_actionPost_register_triggered()
{
    IPlugin *plugZipCodes = Context::instance().plugin("POSTREGISTER");

    if (plugZipCodes != NULL)
    {
        openPlugin(plugZipCodes);
    }
}

void MainWindow::openPlugin(IPlugin *plugin)
{
    ui->tabWidget->setVisible(true);
    ui->dashboard->setVisible(false);

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (ui->tabWidget->widget(i)->objectName() == plugin->pluginId()) {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    if (plugin->ui() != NULL)
    {
        ui->tabWidget->addTab(plugin->ui(), plugin->pluginIcon(), plugin->pluginName());
        ui->tabWidget->widget(ui->tabWidget->count() - 1)->setObjectName(plugin->pluginId());
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }
}

void MainWindow::closeDashboard()
{
    foreach (QFrame *dbFrame, m_dbWidgets) {
        dbFrame->setVisible(false);
    }
}

void MainWindow::openDashboard()
{
    PermissionEvaluator permEv;

    foreach (IPlugin *plugin, Context::instance().plugins()) {
        if (!plugin->dasboardWidgets().isEmpty()
                && permEv.hasPermission(plugin->pluginId(), PERM_READ)) {
            foreach (QFrame *frame, plugin->dasboardWidgets()) {
                if (m_dbWidgets.contains(frame))
                {
                    frame->setVisible(true);
                }
                else
                {
                    ui->dbWidget->layout()->addWidget(frame);
                    m_dbWidgets.append(frame);
                }
            }
        }
    }

    refreshDashboard();
}

void MainWindow::refreshDashboard()
{
    foreach (QFrame *frame, m_dbWidgets) {
        IDashboardWidget *dbWidget = dynamic_cast<IDashboardWidget*>(frame);

        if (dbWidget != nullptr)
        {
            dbWidget->refresh();
        }
    }
}

void MainWindow::closaAllTabs()
{
    ui->tabWidget->setVisible(false);
    ui->dashboard->setVisible(true);

    int tabCount = ui->tabWidget->count();
    for (int i = 0; i < tabCount; i++)
    {
        ui->tabWidget->removeTab(0);
    }
}

void MainWindow::on_actionCountry_register_triggered()
{
    IPlugin *plugCountryReg = Context::instance().plugin("COUNTRYREGISTER");

    if (plugCountryReg != NULL)
    {
        openPlugin(plugCountryReg);
    }

}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About prodejna"), tr("Modular cash register software under GPL license.\n(C) 2015 - 2017 Josef Rokos, Zdenek Jonák"));
}
