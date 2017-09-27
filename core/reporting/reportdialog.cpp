#include "reportdialog.h"
#include "ui_reportdialog.h"

#include <QStandardItemModel>
#include <QIcon>

#include "reportviewer.h"

ReportDialog::ReportDialog(bool recordSelected, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialog)
{
    ui->setupUi(this);
    m_recordSelected = recordSelected;
}

ReportDialog::~ReportDialog()
{
    delete ui;
}

void ReportDialog::setReports(ReportList reports)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->listReports->model());

    if (model == NULL)
    {
        model = new QStandardItemModel(0, 1);
    }
    else
    {
        model->clear();
    }

    foreach (ReportPtr report, reports) {
        QStandardItem *item = new QStandardItem((report->listReport() ? QIcon(":/icons/list.svg") : QIcon(":/icons/report.svg")), report->name());
        item->setEnabled(report->listReport() || m_recordSelected);
        model->appendRow(item);
    }

    ui->listReports->setModel(model);
    m_reports = reports;

    connect(ui->listReports->selectionModel(), &QItemSelectionModel::currentRowChanged, [this](const QModelIndex, QModelIndex){
        ui->textDescription->setText(m_reports[ui->listReports->currentIndex().row()]->description());
        ui->btnPreview->setEnabled(ui->listReports->currentIndex().isValid());
        ui->btnPrint->setEnabled(ui->listReports->currentIndex().isValid());
    });


    if (!reports.isEmpty())
    {
        ui->listReports->setCurrentIndex(model->index(0, 0));
    }
}

void ReportDialog::on_btnPreview_clicked()
{
    ReportViewer *viewer = new ReportViewer(this);
    viewer->setAttribute(Qt::WA_DeleteOnClose);

    viewer->setReport(m_reports[ui->listReports->currentIndex().row()]);
    viewer->openPreview();
}

void ReportDialog::on_btnPrint_clicked()
{
    ReportViewer viever;
    viever.setReport(m_reports[ui->listReports->currentIndex().row()]);
    viever.directPrint();
}

void ReportDialog::on_btnClose_clicked()
{
    close();
}
