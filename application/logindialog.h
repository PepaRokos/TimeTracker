#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    QString login() const;
    QString password() const;
    void reset();

private:
    Ui::LoginDialog *ui;

    // QDialog interface
public slots:
    void accept() override;
};

#endif // LOGINDIALOG_H
