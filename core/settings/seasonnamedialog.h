#ifndef SEASONNAMEDIALOG_H
#define SEASONNAMEDIALOG_H

#include <QDialog>

#include "../data/season.h"
#include "../objectbinder.h"

namespace Ui {
class SeasonNameDialog;
}

class SeasonNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeasonNameDialog(SeasonPtr season, QWidget *parent = 0);
    ~SeasonNameDialog();

private:
    Ui::SeasonNameDialog *ui;
    ObjectBinder m_binder;

    // QDialog interface
public slots:
    void accept();
};

#endif // SEASONNAMEDIALOG_H
