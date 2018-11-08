#include "firststartwizard.h"
#include "ui_firststartwizard.h"

#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <samestringvalidator.h>

FirstStartWizard::FirstStartWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::FirstStartWizard)
{
    ui->setupUi(this);
    m_data.reset(new FirstStartData());

    m_binder.registerBinding(ui->dbFile);
    m_binder.registerBinding(ui->login);
    m_binder.registerBinding(ui->password);
    m_binder.registerBinding(ui->defaultAdmin);
    m_binder.registerBinding(ui->defaultDbPath);
    m_binder.registerBinding(ui->singleUser);

    m_binder.registerValidator(new SameStringValidator(ui->password, ui->retPassword, tr("Passwords does not match")));

    m_binder.setData(m_data.data());
}

FirstStartWizard::~FirstStartWizard()
{
    delete ui;
}

void FirstStartWizard::on_rbCustomDbPath_clicked(bool checked)
{
    ui->dbFile->setEnabled(checked);
}

void FirstStartWizard::on_btnSelectFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Database Files (*.db)"));

    if (!file.isEmpty())
    {
        ui->dbFile->setText(file);
    }
}

bool FirstStartWizard::validateCurrentPage()
{
    if (currentPage() == ui->pageDatabase)
    {
        if (ui->rbCustomDbPath->isChecked() && ui->dbFile->text().isEmpty())
        {
            QMessageBox::critical(this, tr("Error"), tr("Select database file"));
            ui->dbFile->setFocus();
            return false;
        }
    }

    return true;
}

void FirstStartWizard::accept()
{
    if (m_binder.bindToData())
    {
        QWizard::accept();
    }
}

void FirstStartWizard::enableForm(bool enable)
{
    ui->login->setEnabled(enable);
    ui->password->setEnabled(enable);
    ui->retPassword->setEnabled(enable);
}

void FirstStartWizard::on_rbCustomAdmin_clicked()
{
    enableForm(true);
}

FirstStartDataPtr FirstStartWizard::data() const
{
    return m_data;
}

void FirstStartWizard::on_defaultDbPath_clicked()
{
    ui->dbFile->setEnabled(false);
}

void FirstStartWizard::on_defaultAdmin_clicked()
{
    enableForm(false);
}

void FirstStartWizard::on_singleUser_clicked()
{
    enableForm(false);
}
