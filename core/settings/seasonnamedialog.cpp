#include "seasonnamedialog.h"
#include "ui_seasonnamedialog.h"

SeasonNameDialog::SeasonNameDialog(SeasonPtr season, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeasonNameDialog)
{
    ui->setupUi(this);

    m_binder.registerBinding(ui->name);
    m_binder.setData(season.data());
    m_binder.bindToUi();
}

SeasonNameDialog::~SeasonNameDialog()
{
    delete ui;
}

void SeasonNameDialog::accept()
{
    m_binder.bindToData();
    QDialog::accept();
}
