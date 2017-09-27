#ifndef TRACKERSERVICE_H
#define TRACKERSERVICE_H

#include <core.h>
#include "data/tracker-data.h"


class TrackerService : public Service<Project>
{
public:
    TrackerService();
    void loadTimeLog(ProjectPtr project);
    void calculate(ProjectPtr project);
    void saveProject(ProjectPtr project);
    void updateProject(ProjectPtr project);
    void deleteProject(ProjectPtr project);
    TimeLogPtr activeLog(ProjectPtr project);
};

#endif // TRACKERSERVICE_H
