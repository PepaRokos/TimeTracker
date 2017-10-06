#include "trackerservice.h"
#include "tracker-odb.hxx"

TrackerService::TrackerService()
{
}

void TrackerService::loadTimeLog(ProjectPtr project)
{
    Service<TimeLog> srv;
    project->setTimeLog(srv.all(QString("project = %1").arg(project->id())));
}

void TrackerService::calculate(ProjectPtr project)
{
    QDecDouble total;
    int totalMinutes = 0;

    foreach (TimeLogPtr log, project->timeLog()) {
        if (log->end().isValid())
        {
            QDateTime start = log->start();
            QDateTime end = log->end();

            start.setTime(QTime(start.time().hour(), start.time().minute()));
            end.setTime(QTime(end.time().hour(), end.time().minute()));

            quint64 msec = start.msecsTo(end);
            log->setMinutes(msec / 60000);
            log->setPrice(QDecDouble((double)log->minutes() / 60) * log->pricePerHour());

            total += log->price();
            totalMinutes += log->minutes();
        }
    }

    project->setTotalPrice(total);

    QTime timeTotal(0, 0);
    project->setTotalTime(timeTotal.addSecs(totalMinutes * 60));
}

void TrackerService::saveProject(ProjectPtr project)
{
    Transaction tr;
    odb::database *db = Context::instance().db();

    db->persist(project);

    foreach (TimeLogPtr item, project->timeLog()) {
        item->setProject(project.toWeakRef());
        db->persist(item);
    }

    tr.commit();
}

void TrackerService::updateProject(ProjectPtr project)
{
    Transaction tr;
    odb::database *db = Context::instance().db();

    db->execute(QString("DELETE FROM TimeLog WHERE project = %1").arg(project->id()).toStdString());

    foreach (TimeLogPtr item, project->timeLog()) {
        item->setProject(project.toWeakRef());
        db->persist(item);
    }

    db->update(project);

    tr.commit();
}

void TrackerService::deleteProject(ProjectPtr project)
{
    Transaction tr;
    odb::database *db = Context::instance().db();

    db->execute(QString("DELETE FROM TimeLog WHERE project = %1").arg(project->id()).toStdString());
    db->erase(project);

    tr.commit();
}

TimeLogPtr TrackerService::activeLog(ProjectPtr project)
{
    foreach (TimeLogPtr log, project->timeLog()) {
        if (log->end().isNull())
        {
            return log;
        }
    }

    return TimeLogPtr();
}

ProjectSum TrackerService::activeSummary()
{
    Transaction tr;
    odb::database *db = Context::instance().db();

    typedef odb::query<ProjectSum> query;

    ProjectSum sum = db->query_value<ProjectSum>("active = " + query::_ref(true));

    tr.commit();

    return sum;
}

ProjectSum TrackerService::delayedSummary()
{
    Transaction tr;
    odb::database *db = Context::instance().db();

    typedef odb::query<ProjectSum> query;

    ProjectSum sum = db->query_value<ProjectSum>("dueTo < " + query::_ref(QDateTime::currentDateTime()) + " and active = " + query::_ref(true));

    tr.commit();

    return sum;
}
