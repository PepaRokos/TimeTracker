#ifndef TRACKERDATA_H
#define TRACKERDATA_H

class Client;
class Project;
class TimeLog;

#include <QSharedPointer>

typedef QSharedPointer<Client> ClientPtr;
typedef QSharedPointer<Project> ProjectPtr;
typedef QSharedPointer<TimeLog> TimeLogPtr;

#include "client.h"
#include "project.h"
#include "timelog.h"

#endif // TRACKERDATA_H
