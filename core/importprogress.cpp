#include "importprogress.h"
#include "ui_importprogress.h"

ImportProgress::ImportProgress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportProgress)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    m_terminate = false;
}

ImportProgress::~ImportProgress()
{
    delete ui;
}

void ImportProgress::on_btnCancel_clicked()
{
    m_terminate = true;
    this->close();
}

void ImportProgress::updateProgress(int currentPos)
{
    ui->progressBar->setValue(currentPos);
}

bool ImportProgress::terminate()
{
    return m_terminate;
}
