#include "projectdetail.h"
#include "ui_projectdetail.h"

#include "startworkdialog.h"
#include "enddialog.h"
#include "tracker-odb.hxx"
#include "trackerservice.h"

#include <QMessageBox>

ProjectDetail::ProjectDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectDetail)
{
    ui->setupUi(this);

    m_logModel = new AutoTableModel<TimeLog>(this);
    ui->tableView->setModel(m_logModel);

    ui->tableView->setColumnWidth(1, 130);
    ui->tableView->setColumnWidth(2, 130);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    enableButtons();
}

ProjectDetail::~ProjectDetail()
{
    delete ui;
}

void ProjectDetail::setCurrent(ProjectPtr project)
{
    m_currentProject = project;
    ui->totalPrice->setText(QString::number(m_currentProject->totalPrice().toDouble()));
    ui->totalTime->setText(project->totalTime().toString("H:mm"));
    m_logModel->setData(m_currentProject->timeLog());

    enableButtons();
}

void ProjectDetail::on_btnStart_clicked()
{
    StartWorkDialog *dlg = new StartWorkDialog(m_currentProject->pricePerHour(), this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    connect(dlg, &QDialog::accepted, [this, dlg](){
        m_currentProject->addTimeLog(dlg->log());
        TrackerService srv;
        srv.updateProject(m_currentProject);
        m_logModel->setData(m_currentProject->timeLog());

        enableButtons();
    });
}

void ProjectDetail::on_btnStop_clicked()
{
    EndDialog *dlg = new EndDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    connect(dlg, &QDialog::accepted, [this, dlg](){
        TrackerService srv;
        TimeLogPtr lastLog = srv.activeLog(m_currentProject);

        if (!lastLog.isNull())
        {
            lastLog->setEnd(dlg->end());
            srv.calculate(m_currentProject);
            srv.updateProject(m_currentProject);

            ui->totalPrice->setText(QString::number(m_currentProject->totalPrice().toDouble()));
            ui->totalTime->setText(m_currentProject->totalTime().toString("H:mm"));

            enableButtons();
        }
    });
}

void ProjectDetail::on_btnRemoveLast_clicked()
{
    m_currentProject->removeLastLog();
    TrackerService srv;

    srv.calculate(m_currentProject);
    srv.updateProject(m_currentProject);

    m_logModel->setData(m_currentProject->timeLog());
    ui->totalPrice->setText(QString::number(m_currentProject->totalPrice().toDouble()));
    ui->totalTime->setText(m_currentProject->totalTime().toString("H:mm"));

    enableButtons();
}

void ProjectDetail::enableButtons()
{
    bool disableAll = m_currentProject.isNull();
    TimeLogPtr lastLog = disableAll ? TimeLogPtr() : (m_currentProject->timeLog().isEmpty() ? TimeLogPtr() : m_currentProject->timeLog().last());
    bool isStarted = lastLog.isNull() ? false : !lastLog->end().isValid();

    ui->btnStart->setEnabled(!disableAll && !isStarted && m_currentProject->active());
    ui->btnStop->setEnabled(!disableAll && isStarted && m_currentProject->active());
    ui->btnRemoveLast->setEnabled(!disableAll && !isStarted && m_currentProject->active());
    ui->btnDone->setEnabled(!disableAll && !isStarted && m_currentProject->active());
    ui->btnReactivate->setEnabled(!disableAll && !isStarted && !m_currentProject->active());
}

void ProjectDetail::on_btnDone_clicked()
{
    EndDialog *dlg = new EndDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    connect(dlg, &QDialog::accepted, [this, dlg](){
        m_currentProject->setEnd(dlg->end());
        m_currentProject->setActive(false);

        TrackerService srv;
        srv.updateProject(m_currentProject);

        enableButtons();
    });
}

void ProjectDetail::on_btnReactivate_clicked()
{
    if (QMessageBox::question(this, tr("Reactivate project"), tr("Do you want reactivate this project?")) == QMessageBox::Yes)
    {
        m_currentProject->setEnd(QDateTime());
        m_currentProject->setActive(true);

        TrackerService srv;
        srv.updateProject(m_currentProject);

        enableButtons();
    }
}
