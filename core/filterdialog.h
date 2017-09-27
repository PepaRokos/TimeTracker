#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QString>
#include <QTableWidget>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = 0);
    ~FilterDialog();

    QString pluginId() const;
    void setPluginId(const QString &pluginId);
    QTableWidget *table();

private:
    Ui::FilterDialog *ui;
    QString m_pluginId;

    void fillTable();
};

#endif // FILTERDIALOG_H
