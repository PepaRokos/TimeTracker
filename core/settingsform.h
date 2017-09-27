#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QDialog>

#include "core_global.h"

namespace Ui {
class SettingsForm;
}

class CORESHARED_EXPORT SettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SettingsForm *ui;

    // QDialog interface
public slots:
    void accept() override;
};

#endif // SETTINGSFORM_H
