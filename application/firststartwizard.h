#ifndef FIRSTSTARTWIZARD_H
#define FIRSTSTARTWIZARD_H

#include <QWizard>

#include <core.h>
#include "firststartdata.h"

namespace Ui {
class FirstStartWizard;
}

class FirstStartWizard : public QWizard
{
    Q_OBJECT

public:
    explicit FirstStartWizard(QWidget *parent = 0);
    ~FirstStartWizard();
    FirstStartDataPtr data() const;

private slots:
    void on_rbCustomDbPath_clicked(bool checked);

    void on_btnSelectFile_clicked();

    void on_rbCustomAdmin_clicked();

    void on_defaultDbPath_clicked();

    void on_defaultAdmin_clicked();

    void on_singleUser_clicked();

private:
    Ui::FirstStartWizard *ui;
    ObjectBinder m_binder;
    FirstStartDataPtr m_data;

    void enableForm(bool enable);

    // QWizard interface
public:
    virtual bool validateCurrentPage() override;

    // QDialog interface
public slots:
    virtual void accept() override;
};

#endif // FIRSTSTARTWIZARD_H
