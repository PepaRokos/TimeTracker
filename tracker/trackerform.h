#ifndef TRACKERFORM_H
#define TRACKERFORM_H

#include <QWidget>
#include <core.h>
#include "data/project.h"
#include "tracker-odb.hxx"

namespace Ui {
class TrackerForm;
}

class TrackerForm : public AutoForm<Project>
{
    Q_OBJECT

public:
    explicit TrackerForm(QWidget *parent = 0);
    ~TrackerForm();

private:
    Ui::TrackerForm *ui;

    // FormBinder interface
protected:
    void registerCombos();
private slots:
    void on_btnNewClient_clicked();
};

#endif // TRACKERFORM_H
