#ifndef STARTWORKDIALOG_H
#define STARTWORKDIALOG_H

#include <QDialog>
#include <QDateTime>
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
    void setRefDateTime(const QDateTime &dateTime);

private:
    Ui::StartWorkDialog *ui;
    TimeLogPtr m_timeLog;
    ObjectBinder m_binder;
    QDateTime m_refDateTime;

    // QDialog interface
public slots:
    void accept();
};

#endif // STARTWORKDIALOG_H
