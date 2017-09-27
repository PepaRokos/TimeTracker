#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QMetaObject>
#include "iservice.h"

#include "core_global.h"

namespace Ui {
class ImportDialog;
}

class CORESHARED_EXPORT ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = 0);
    ~ImportDialog();

    QString fileName();
    QString separator();

private slots:
    void on_btnFile_clicked();

private:
    Ui::ImportDialog *ui;
};

#endif // IMPORTDIALOG_H
