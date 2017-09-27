#include "tracker.h"

#include "trackergrid.h"
#include "trackerform.h"
#include "trackerservice.h"

Tracker::Tracker()
{
}

void Tracker::initServiceUi()
{
    TrackerGrid *grid = new TrackerGrid();
    TrackerForm *form = new TrackerForm();

    m_service = new TrackerService();
    m_ui = grid;
    ((TrackerGrid *) m_ui)->setForm(form);
}

QIcon Tracker::pluginIcon()
{
    return QIcon(":/icons/tracker_48x48.png");
}
