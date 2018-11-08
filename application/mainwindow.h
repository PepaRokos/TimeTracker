#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>

#include "logindialog.h"

#define PLUGIN_INDEX "plug_index"

class IPlugin;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void openPlugin();

    void on_actionOpen_database_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionLogin_triggered();

    void on_actionSettings_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    LoginDialog *m_loginDialog;
    QLabel *m_lblUser;
    QList<QFrame*> m_dbWidgets;

    void openPlugin(IPlugin *plugin);
    void closeDashboard();
    void openDashboard();
    void refreshDashboard();
    void closaAllTabs();
    void initDatabase();
    void openDatabase(const QString &dbPath);

    // QWidget interface
protected:
    void showEvent(QShowEvent *evt);
    void closeEvent(QCloseEvent *evt) override;
};

#endif // MAINWINDOW_H
