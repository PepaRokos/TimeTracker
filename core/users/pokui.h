#ifndef POKUI_H
#define POKUI_H

#include <QWidget>

namespace Ui {
    class GridForm;
}


class PokUi : public QWidget
{
    Q_OBJECT
public:
    explicit PokUi(QWidget *parent = 0);
    ~PokUi();

signals:

public slots:

private:
    Ui::GridForm *ui;
};

#endif // POKUI_H
