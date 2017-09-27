#ifndef IGRIDFORM_H
#define IGRIDFORM_H

#include <QWidget>
#include <QString>
#include <QTableView>
#include <QMenu>
#include <QList>
#include <QVBoxLayout>
#include <QWidget>

#include "columndialog.h"
#include "filterui.h"
#include "defaultformhandler.h"
#include "core_global.h"
#include "reporting/variablefiller.h"

namespace Ui {
    class GridForm;
}

class CORESHARED_EXPORT IGridForm : public QWidget
{
    Q_OBJECT

public:
    explicit IGridForm(QWidget *parent = 0);
    virtual ~IGridForm();

    void setPluginId(const QString &pluginId);
    QString pluginId();
    QTableView *tableView();
    QWidget *toolbar();
    virtual void setTranslations(const QMap<QString, QString> &translations) = 0;
    void setReportVarFiller(VariableFiller *filler);

signals:
    void dataChanged();

public slots:
    virtual bool fillData() = 0;

protected:
    virtual void handleNewRecord() = 0;
    virtual void handleEditRecord() = 0;
    virtual void handleDeleteRecord() = 0;
    virtual bool canAddRecord() { return true; }
    virtual bool canEditRecord() { return true; }
    virtual bool canDeleteRecord() { return true; }
    virtual int currentRecordId() = 0;
    virtual void currentIndexChanged(const QModelIndex &current) { Q_UNUSED(current) }
    void hideColumns(const QList<int> &cols);
    QWidget *filterWidget();
    QVBoxLayout *mainLayout();
    void enableButtons();

private slots:
    void on_btnNew_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void on_actionSelectColumns_triggered();
    void columnsAccepted();
    void widthChanged(int logicalIndex, int oldSize, int newSize);

    void on_btnFilter_toggled(bool checked);

    void on_tableView_clicked(const QModelIndex &index);

    void on_btnPrint_clicked();

private:
    QString m_pluginId;
    IFormHandler *m_formHandler;
    Ui::GridForm *ui;
    QMenu *m_contextMenu;
    ColumnDialog *m_columnDialog;
    VariableFiller *m_varFiller;

protected:
    FilterUi *m_filterUi;
    IForm *m_form;
};

#endif // IGRIDFORM_H
