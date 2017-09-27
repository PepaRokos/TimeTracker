#include "trackergrid.h"
#include "trackerservice.h"

TrackerGrid::TrackerGrid(QWidget *parent) : GridForm<Project>(parent)
{
    setTableModel(new AutoTableModel<Project>());

    m_detail = new ProjectDetail(this);
    mainLayout()->addWidget(m_detail);
}

void TrackerGrid::currentIndexChanged(const QModelIndex &)
{
    m_detail->setCurrent(this->currentEntity());
}

void TrackerGrid::doDelete(ProjectPtr entity)
{
    TrackerService *srv = dynamic_cast<TrackerService*>(Context::instance().plugin("TIMETRACKER")->service<Project>());
    if (srv != nullptr)
    {
        srv->deleteProject(entity);
    }
}
