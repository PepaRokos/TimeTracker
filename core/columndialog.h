#ifndef COLUMNDIALOG_H
#define COLUMNDIALOG_H

#include <QDialog>
#include <QObject>
#include <QTableView>
#include <QList>

namespace Ui {
class ColumnDialog;
}

class ColumnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColumnDialog(QWidget *parent = 0);
    ~ColumnDialog();

    void setTable(QTableView *table);
    QList<int> columnsToHide();

private:
    Ui::ColumnDialog *ui;
};

#endif // COLUMNDIALOG_H
