#include "ui_gridform.h"
#include "pokui.h"

PokUi::PokUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GridForm)
{
    ui->setupUi(this);
}

PokUi::~PokUi()
{
    delete ui;
}
