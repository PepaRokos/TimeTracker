#ifndef TRACKERGRID_H
#define TRACKERGRID_H

#include <QWidget>
#include <core.h>

#include "projectdetail.h"

#include "data/project.h"
#include "tracker-odb.hxx"

class TrackerGrid : public GridForm<Project>
{
    Q_OBJECT
public:
    explicit TrackerGrid(QWidget *parent = 0);

signals:

public slots:

private:
    ProjectDetail *m_detail;

    // IGridForm interface
protected:
    void currentIndexChanged(const QModelIndex &current);

    // GridForm interface
protected:
    virtual void doDelete(ProjectPtr entity) override;
};

#endif // TRACKERGRID_H
