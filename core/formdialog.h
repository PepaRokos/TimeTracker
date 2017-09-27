#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include <QDialog>
#include <QWidget>

#include "iform.h"

namespace Ui {
class FormDialog;
}

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormDialog(QWidget *parent = 0);
    ~FormDialog();

    void setForm(IForm *formWidget);

private:
    bool m_formSet;
    IForm *m_form;
    Ui::FormDialog *ui;

private slots:
    void onValidationError(const QString &message);

    // QDialog interface
public slots:
    void accept();

    // QDialog interface
public slots:
    void reject() override;
};

#endif // FORMDIALOG_H
