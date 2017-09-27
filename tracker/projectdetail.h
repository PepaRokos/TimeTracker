#ifndef PROJECTDETAIL_H
#define PROJECTDETAIL_H

#include <QWidget>
#include "data/tracker-data.h"
#include "core.h"

namespace Ui {
class ProjectDetail;
}

class ProjectDetail : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectDetail(QWidget *parent = 0);
    ~ProjectDetail();
    void setCurrent(ProjectPtr project);

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnRemoveLast_clicked();

    void on_btnDone_clicked();

    void on_btnReactivate_clicked();

private:
    Ui::ProjectDetail *ui;
    ProjectPtr m_currentProject;
    AutoTableModel<TimeLog> *m_logModel;

    void enableButtons();
};

#endif // PROJECTDETAIL_H
