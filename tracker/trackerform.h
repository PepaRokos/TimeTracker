#ifndef TRACKERFORM_H
#define TRACKERFORM_H

#include <QWidget>
#include <QDateTimeEdit>
#include <core.h>
#include "data/project.h"
#include "tracker-odb.hxx"

#include <addresswidget.h>

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

    AddressWidget *m_addrWidget;
    bool m_newClient;

    // FormBinder interface
protected:
    void bindOtherToUi();
    bool bindOtherToData();

};

#endif // TRACKERFORM_H
