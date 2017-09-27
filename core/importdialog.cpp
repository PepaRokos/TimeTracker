#include "importdialog.h"
#include "ui_importdialog.h"
#include "importprogress.h"
#include "csvimporter.h"

#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

QString ImportDialog::fileName()
{
    return ui->editFile->text();
}

QString ImportDialog::separator()
{
    return ui->editSeparator->text();
}

void ImportDialog::on_btnFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Import file"), "", tr("All Files (*.*)"));
    ui->editFile->setText(file);
}
