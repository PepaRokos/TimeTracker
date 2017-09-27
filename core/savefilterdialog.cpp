#include "savefilterdialog.h"
#include "ui_savefilterdialog.h"

SaveFilterDialog::SaveFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveFilterDialog)
{
    ui->setupUi(this);
}

SaveFilterDialog::~SaveFilterDialog()
{
    delete ui;
}

QString SaveFilterDialog::filterName()
{
    return ui->filterName->text();
}
