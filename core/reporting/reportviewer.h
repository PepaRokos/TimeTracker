#ifndef REPORTVIEWER_H
#define REPORTVIEWER_H

#include <QDialog>
#include "report.h"
#include "core_global.h"

namespace Ui {
class ReportViewer;
}

namespace LimeReport {
class PreviewReportWidget;
class ReportEngine;
}

class CORESHARED_EXPORT ReportViewer : public QDialog
{
    Q_OBJECT

public:
    explicit ReportViewer(QWidget *parent = 0);
    ~ReportViewer();
    void setReport(ReportPtr report);
    void openPreview();
    void directPrint(bool dialog = true);

private slots:
    void on_btnClose_clicked();

    void on_btnEdit_clicked();

    void slotPageSet(int page);

private:
    Ui::ReportViewer *ui;

    LimeReport::PreviewReportWidget *m_prevWidget;
    LimeReport::ReportEngine *m_report;
};

#endif // REPORTVIEWER_H
