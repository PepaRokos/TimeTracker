#ifndef FILTERUI_H
#define FILTERUI_H

#include <QWidget>
#include <QMenu>
#include <QComboBox>

#include "core_global.h"

namespace Ui {
class FilterUi;
}

class CORESHARED_EXPORT FilterUi : public QWidget
{
    Q_OBJECT

public:
    explicit FilterUi(QWidget *parent = 0, QObject *entity = NULL);
    ~FilterUi();

    QString pluginId() const;
    void setPluginId(const QString &pluginId);

private slots:
    void on_actionAdd_condition_AND_triggered();
    void on_actionAdd_condition_OR_triggered();
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void on_actionRemove_condition_triggered();
    void on_btnGo_toggled(bool checked);

    void on_btnSave_clicked();

    void on_comboLoad_currentIndexChanged(int index);

    void on_btnManage_clicked();

signals:
    void applyFilter(const QString &filter);
    void restoreData();

private:
    Ui::FilterUi *ui;
    void addRow(bool isOr);
    QObject *m_entity;
    QMenu *m_contextMenu;
    QString m_pluginId;
    bool m_buildGrid;

    QString buildExpression() const;
    void propertyChanged(int row, QComboBox *oper, int index);
    void fillCombo();
    void buildGrid(const QString &expr);
};

#endif // FILTERUI_H
