#ifndef STARTWORKDIALOG_H
#define STARTWORKDIALOG_H

#include <QDialog>
#include "data/timelog.h"
#include <core.h>

namespace Ui {
class StartWorkDialog;
}

class StartWorkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartWorkDialog(QDecDouble pricePerHour, QWidget *parent = 0);
    ~StartWorkDialog();
    TimeLogPtr log();

private:
    Ui::StartWorkDialog *ui;
    TimeLogPtr m_timeLog;
    ObjectBinder m_binder;

    // QDialog interface
public slots:
    void accept();
};

#endif // STARTWORKDIALOG_H
