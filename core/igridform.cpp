#include "igridform.h"
#include "ui_gridform.h"

#include <QList>
#include <QDebug>
#include <QMap>
#include <QItemSelectionModel>

#include "context.h"
#include "filterui.h"
#include "iplugin.h"
#include "reporting/reportdialog.h"

IGridForm::IGridForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GridForm)
{
    ui->setupUi(this);
    ui->filterWidget->setVisible(false);
    m_contextMenu = new QMenu(this);
    m_contextMenu->addAction(ui->actionSelectColumns);
    m_form = NULL;

    m_columnDialog = new ColumnDialog(this);
    connect(m_columnDialog, SIGNAL(accepted()), this, SLOT(columnsAccepted()));

    m_varFiller = new VariableFiller();
}

IGridForm::~IGridForm()
{
    if (m_varFiller != NULL)
    {
        delete m_varFiller;
    }

    delete ui;
}

void IGridForm::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;

    if (m_filterUi != NULL)
    {
        m_filterUi->setPluginId(pluginId);
    }

    if (m_form != NULL)
    {
        m_form->setPluginId(pluginId);
    }
}

QString IGridForm::pluginId()
{
    return m_pluginId;
}

QTableView *IGridForm::tableView()
{
    return ui->tableView;
}

QWidget *IGridForm::toolbar()
{
    return ui->widget;
}

void IGridForm::setReportVarFiller(VariableFiller *filler)
{
    if (m_varFiller != NULL)
    {
        delete m_varFiller;
    }

    m_varFiller = filler;
}

void IGridForm::hideColumns(const QList<int> &cols)
{
    foreach (int col, cols) {
        tableView()->setColumnHidden(col, true);
    }
}

QWidget *IGridForm::filterWidget()
{
    return ui->filterWidget;
}

QVBoxLayout *IGridForm::mainLayout()
{
    return ui->verticalLayout;
}

void IGridForm::enableButtons()
{
    ui->btnNew->setEnabled(canAddRecord());

    if (ui->tableView->currentIndex().isValid())
    {
        ui->btnEdit->setEnabled(canEditRecord());
        ui->btnDelete->setEnabled(canDeleteRecord());
    }
}


void IGridForm::on_btnNew_clicked()
{
    handleNewRecord();
}

void IGridForm::on_btnEdit_clicked()
{
    handleEditRecord();
}

void IGridForm::on_btnDelete_clicked()
{
    handleDeleteRecord();
}

void IGridForm::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    m_contextMenu->popup(tableView()->viewport()->mapToGlobal(pos));
}

void IGridForm::on_actionSelectColumns_triggered()
{
    m_columnDialog->setTable(tableView());
    m_columnDialog->show();
}

void IGridForm::columnsAccepted()
{
    for(int i = 0; i < tableView()->model()->columnCount(); i++)
    {
        tableView()->setColumnHidden(i, false);
    }

    QList<int> hide = m_columnDialog->columnsToHide();
    hideColumns(hide);

    QList<QVariant> varList;

    foreach (int i, hide) {
        varList.append(i);
    }

    Context::instance().settings()->setValue("grids/" + pluginId() + "/hide", QVariant::fromValue(varList));
}

void IGridForm::widthChanged(int logicalIndex, int oldSize, int newSize)
{
    Q_UNUSED(oldSize);

    QMap<QString, QVariant> widths = Context::instance().settings()->value("grids/" + pluginId() + "/widths").toMap();
    widths[QString::number(logicalIndex)] = newSize;
    Context::instance().settings()->setValue("grids/" + pluginId() + "/widths", QVariant::fromValue(widths));
}


void IGridForm::on_btnFilter_toggled(bool checked)
{
    if (checked)
    {
        ui->filterWidget->setVisible(true);
    }
    else
    {
        ui->filterWidget->setVisible(false);
    }
}

void IGridForm::on_tableView_clicked(const QModelIndex &)
{
    enableButtons();
}

void IGridForm::on_btnPrint_clicked()
{
    ReportDialog *dialog = new ReportDialog(currentRecordId() != 0, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    if (m_varFiller != NULL)
    {
        m_varFiller->fillList(Context::instance().plugin(pluginId())->reports(), currentRecordId());
    }

    dialog->setReports(Context::instance().plugin(pluginId())->reports());
    dialog->show();
}
