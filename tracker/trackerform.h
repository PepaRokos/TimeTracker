#ifndef TRACKERFORM_H
#define TRACKERFORM_H

#include <QWidget>
#include <QDateTimeEdit>
#include <core.h>
#include "data/project.h"
#include "tracker-odb.hxx"

class DateValidator : public IValidator
{
public:
    DateValidator(QWidget *widget, const QString &message, QDateTimeEdit *startEdit);

    // IValidator interface
public:
    virtual bool validate() override;

private:
    QDateTimeEdit *m_startEdit;
};

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
