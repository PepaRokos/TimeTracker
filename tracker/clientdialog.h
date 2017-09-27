#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <core.h>

#include "data/client.h"

namespace Ui {
class ClientDialog;
}

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = 0);
    ~ClientDialog();

    ClientPtr client();

private:
    Ui::ClientDialog *ui;
    ObjectBinder m_binder;
    ClientPtr m_client;

    // QDialog interface
public slots:
    void accept();
};

#endif // CLIENTDIALOG_H
