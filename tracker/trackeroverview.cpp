#include "trackeroverview.h"
#include "ui_trackeroverview.h"
#include "trackerservice.h"

TrackerOverview::TrackerOverview(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TrackerOverview)
{
    ui->setupUi(this);
}

TrackerOverview::~TrackerOverview()
{
    delete ui;
}

void TrackerOverview::refresh()
{
    TrackerService srv;

    ProjectSum activeSum = srv.activeSummary();
    ProjectSum delayedSum = srv.delayedSummary();

    ui->labelActiveCount->setText(QString::number(activeSum.m_count));
    ui->labelActivePrice->setText(QString::number(activeSum.totalPrice().toDouble()));
    ui->labelDelayed->setText(QString::number(delayedSum.m_count));
}
