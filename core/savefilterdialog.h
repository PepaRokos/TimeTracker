#ifndef SAVEFILTERDIALOG_H
#define SAVEFILTERDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SaveFilterDialog;
}

class SaveFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveFilterDialog(QWidget *parent = 0);
    ~SaveFilterDialog();

    QString filterName();

private slots:

private:
    Ui::SaveFilterDialog *ui;
};

#endif // SAVEFILTERDIALOG_H
