#ifndef TRACKEROVERVIEW_H
#define TRACKEROVERVIEW_H

#include <QFrame>
#include <idashboardwidget.h>

namespace Ui {
class TrackerOverview;
}

class TrackerOverview : public QFrame, public IDashboardWidget
{
    Q_OBJECT

public:
    explicit TrackerOverview(QWidget *parent = 0);
    ~TrackerOverview();

    // IDashboardWidget interface
    virtual void refresh() override;

private:
    Ui::TrackerOverview *ui;
};

#endif // TRACKEROVERVIEW_H
