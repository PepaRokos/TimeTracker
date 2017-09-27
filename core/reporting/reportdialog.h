#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>
#include "report.h"

namespace Ui {
class ReportDialog;
}

class ReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportDialog(bool recordSelected = false, QWidget *parent = 0);
    ~ReportDialog();

    void setReports(ReportList reports);

private slots:
    void on_btnPreview_clicked();

    void on_btnPrint_clicked();

    void on_btnClose_clicked();

private:
    Ui::ReportDialog *ui;
    ReportList m_reports;
    bool m_recordSelected;
};

#endif // REPORTDIALOG_H
