#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core.h>

#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

#include "firststartwizard.h"
#include "firststartdata.h"

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
        openDatabase(dbFile);

        if (Context::instance().currentUser().isNull())
        {
            m_loginDialog->show();
        }
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

    initDatabase();

    if (Context::instance().db() != NULL)
    {
        ui->navigation->setEnabled(true);
    }

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

    if (!Context::instance().currentUser().isNull())
    {
        m_lblUser->setText(Context::instance().currentUser()->name());
        ui->labelUser->setText(Context::instance().currentUser()->name());
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

void MainWindow::initDatabase()
{
    QString dbPath = Context::instance().settings()->value("db/path", "").toString();

    if (dbPath.isEmpty())
    {
        FirstStartWizard *wizard = new FirstStartWizard(this);
        wizard->setAttribute(Qt::WA_DeleteOnClose);

        wizard->show();

        connect(wizard, &QDialog::accepted, [this, wizard](){
            FirstStartDataPtr data = wizard->data();
            QString dbPath;

            if (data->defaultDbPath())
            {
                QString dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.timetracker/";

                if (!QDir(dir).exists())
                {
                    QDir().mkdir(dir);
                }

                dbPath = dir + "data.db";
            }
            else
            {
                dbPath = data->dbFile();
            }

            Context::instance().openDb(dbPath);

            PermissionService permSrv;
            QSharedPointer<User> user = permSrv.loadUser("admin");

            if (data->singleUser())
            {
                Context::instance().setCurrentUser(user);

                SettingsService setSrv("CORE");
                GlobalSettingsPtr settings = setSrv.loadSettings<GlobalSettings>();

                settings->setSingleUser(true);
                setSrv.saveSettings(settings);

                openDashboard();

                ui->actionLogin->setEnabled(false);
            }

            if (!data->defaultAdmin() && !data->singleUser())
            {
                user->setLogin(data->login());
                user->setPassword(permSrv.encryptPassword(data->password()));

                UserService userSrv;
                userSrv.updateUser(user);
            }

            ui->navigation->setEnabled(true);
        });

        connect(wizard, &QDialog::rejected, [this](){
            this->close();
        });
    }
    else
    {
        openDatabase(dbPath);
    }
}

void MainWindow::openDatabase(const QString &dbPath)
{
    Context::instance().openDb(dbPath);

    SettingsService setSrv("CORE");
    GlobalSettingsPtr settings = setSrv.loadSettings<GlobalSettings>();

    if (settings->singleUser())
    {
        PermissionService permSrv;
        QSharedPointer<User> user = permSrv.adminUser();
        Context::instance().setCurrentUser(user);

        openDashboard();

        ui->actionLogin->setEnabled(false);
    }
    else
    {
        ui->actionLogin->setEnabled(true);
        Context::instance().setCurrentUser(QSharedPointer<User>());
    }

    ui->navigation->setEnabled(true);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About TimeTracker"), tr("Modular project time tracking software under GPL license.\n(C) 2015 - 2017 Josef Rokos, Zdenek Jonák"));
}
