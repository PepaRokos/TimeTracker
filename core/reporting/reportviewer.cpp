#include "reportviewer.h"
#include "ui_reportviewer.h"

#include "../context.h"

#include <QFile>
#include <QPrinter>
#include <LimeReport>

ReportViewer::ReportViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportViewer)
{
    ui->setupUi(this);
    m_report = NULL;
}

ReportViewer::~ReportViewer()
{
    delete ui;
}

void ReportViewer::setReport(ReportPtr report)
{
    m_report = new LimeReport::ReportEngine(this);

    QString reportPath = qApp->applicationDirPath() + REPORT_ROOT + "/" + report->file();
    QFile file(reportPath);
    file.open(QFile::ReadOnly);

    QByteArray data = file.readAll();
    m_report->loadFromByteArray(&data);
    m_report->setReportFileName(reportPath);
    m_report->dataManager()->setReportVariable("dbPath", Context::instance().settings()->value("db/path", "").toString());

    foreach (QString key, report->variables().keys()) {
        m_report->dataManager()->setReportVariable(key, report->variables()[key]);
    }
}

void ReportViewer::openPreview()
{
    Q_ASSERT(m_report != NULL);

    showMaximized();

    m_prevWidget = m_report->createPreviewWidget(this);

    connect(m_prevWidget, SIGNAL(pagesSet(int)), this, SLOT(slotPageSet(int)));
    connect(ui->pageNavigator, SIGNAL(valueChanged(int)), m_prevWidget, SLOT(pageNavigatorChanged(int)));
    connect(ui->btnPrint, SIGNAL(clicked(bool)), m_prevWidget, SLOT(print()));
    connect(ui->btnPdf, SIGNAL(clicked(bool)), m_prevWidget, SLOT(printToPDF()));
    connect(ui->btnPageUp, SIGNAL(clicked(bool)), m_prevWidget, SLOT(priorPage()));
    connect(ui->btnPageDown, SIGNAL(clicked(bool)), m_prevWidget, SLOT(nextPage()));
    connect(ui->btnZoomIn, SIGNAL(clicked(bool)), m_prevWidget, SLOT(zoomIn()));
    connect(ui->btnZoomOut, SIGNAL(clicked(bool)), m_prevWidget, SLOT(zoomOut()));
    connect(ui->btnFitHoriz, SIGNAL(clicked(bool)), m_prevWidget, SLOT(fitWidth()));
    connect(ui->btnFitVert, SIGNAL(clicked(bool)), m_prevWidget, SLOT(fitPage()));

    ui->reportLayout->addWidget(m_prevWidget);
    m_prevWidget->refreshPages();
}

void ReportViewer::directPrint(bool dialog)
{
    Q_ASSERT(m_report != NULL);

    QPrinter printer(QPrinter::HighResolution);

    if (dialog || !printer.isValid())
    {
        m_report->printReport();
    }
    else
    {
        m_report->printReport(&printer);
    }
}

void ReportViewer::on_btnClose_clicked()
{
    close();
}

void ReportViewer::on_btnEdit_clicked()
{
    m_report->designReport();
}

void ReportViewer::slotPageSet(int page)
{
    ui->pageNavigator->setSuffix(ui->pageNavigator->suffix() + QString::number(page));
    ui->pageNavigator->setMinimum(1);
    ui->pageNavigator->setMaximum(page);
}
