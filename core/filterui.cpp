#include "filterui.h"
#include "ui_filterui.h"

#include <QComboBox>
#include <QMetaProperty>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QToolButton>
#include <QList>
#include <QMap>
#include <QVariant>

#include "savefilterdialog.h"
#include "filterdialog.h"
#include "context.h"

FilterUi::FilterUi(QWidget *parent, QObject *entity) :
    QWidget(parent),
    ui(new Ui::FilterUi)
{
    ui->setupUi(this);
    m_entity = entity;
    m_buildGrid = true;

    if (entity == NULL)
    {
        return;
    }

    m_entity->setParent(this);
    addRow(false);

    m_contextMenu = new QMenu(this);
    m_contextMenu->addAction(ui->actionAdd_condition_AND);
    m_contextMenu->addAction(ui->actionAdd_condition_OR);
}

FilterUi::~FilterUi()
{
    delete ui;
}

void FilterUi::on_actionAdd_condition_AND_triggered()
{
    addRow(false);
}

void FilterUi::on_actionAdd_condition_OR_triggered()
{
    addRow(true);
}

void FilterUi::addRow(bool isOr)
{
    if (m_entity == NULL)
    {
        Q_ASSERT(false);
        return;
    }

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
    QComboBox *properties = new QComboBox(this);

    for (int i = 1; i < m_entity->metaObject()->propertyCount(); i++)
    {
        properties->addItem(tr(m_entity->metaObject()->property(i).name()), m_entity->metaObject()->property(i).name());
    }

    QComboBox *oper = new QComboBox(this);
    oper->addItems(QStringList() << "==" << "%" << "!=" << "<" << "<=" << ">" << ">=");
    ui->tableWidget->setCellWidget(row, 2, oper);

    void (QComboBox::*indexChanged)(int) = &QComboBox::currentIndexChanged;
    connect(properties, indexChanged, [this, oper, row](int index){
        this->propertyChanged(row, oper, index);
    });

    ui->tableWidget->setCellWidget(row, 1, properties);

    if (row > 0)
    {
        QComboBox *rowOper = new QComboBox(this);
        rowOper->addItems(QStringList() << tr("OR") << tr("AND"));
        rowOper->setCurrentIndex(isOr ? 0 : 1);
        ui->tableWidget->setCellWidget(row, 0, rowOper);

        QToolButton *tb = new QToolButton(this);
        tb->setText("-");
        connect(tb, &QToolButton::clicked, [this, tb](){
            int row = ui->tableWidget->rowAt(tb->y());
            ui->tableWidget->removeRow(row);
        });
        ui->tableWidget->setCellWidget(row, 4, tb);
    }
    else
    {
        ui->tableWidget->setColumnWidth(1, 150);
        ui->tableWidget->setColumnWidth(2, 50);
        ui->tableWidget->setColumnWidth(3, 300);
        ui->tableWidget->setColumnWidth(4, 50);
    }

    propertyChanged(row, oper, 0);
}

QString FilterUi::pluginId() const
{
    return m_pluginId;
}

void FilterUi::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;
    fillCombo();
}

QString FilterUi::buildExpression() const
{
    QString expr;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        if (i == 0)
        {
            expr = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 1))->currentData(Qt::UserRole).toString();
        }
        else
        {
            expr += " " + QString(qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 0))->currentIndex() == 0 ? "||" : "&&");
            expr += " " + qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 1))->currentData(Qt::UserRole).toString();
        }

        expr += " " + qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 2))->currentText();

        QWidget *cellWidget = ui->tableWidget->cellWidget(i, 3);

        if (cellWidget != NULL)
        {
            expr += " " + cellWidget->property(cellWidget->metaObject()->userProperty().name()).toString().replace(" ", "%20");
        }
    }

    return expr;
}


void FilterUi::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    m_contextMenu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
}

void FilterUi::on_actionRemove_condition_triggered()
{
    QObject *action = sender();
    ui->tableWidget->removeRow(action->property("row").toInt());
}

void FilterUi::on_btnGo_toggled(bool checked)
{
    if (checked)
    {
        emit applyFilter(buildExpression());
    }
    else
    {
        emit restoreData();
    }
}

void FilterUi::propertyChanged(int row, QComboBox *oper, int index)
{
    QWidget *cellWidget = ui->tableWidget->cellWidget(row, 3);
    ui->tableWidget->removeCellWidget(row, 3);

    if (cellWidget != NULL)
    {
        delete cellWidget;
        cellWidget = NULL;
    }

    oper->clear();

    switch (this->m_entity->metaObject()->property(index + 1).type()) {
    case QVariant::Bool:
        oper->addItems(QStringList() << "==" << "!=");
        cellWidget = new QComboBox(this);
        qobject_cast<QComboBox*>(cellWidget)->addItem("true", 1);
        qobject_cast<QComboBox*>(cellWidget)->addItem("false", 0);
        break;
    case QVariant::String:
        oper->addItems(QStringList() << "==" << "%" << "!=" << "<" << "<=" << ">" << ">=");
        cellWidget = new QLineEdit(this);
        break;
    case QVariant::Int:
        oper->addItems(QStringList() << "==" << "!=" << "<" << "<=" << ">" << ">=");
        cellWidget = new QSpinBox(this);
        break;
    case QVariant::Double:
        oper->addItems(QStringList() << "==" << "!=" << "<" << "<=" << ">" << ">=");
        cellWidget = new QDoubleSpinBox(this);
        break;
    case QVariant::Date:
        oper->addItems(QStringList() << "==" << "!=" << "<" << "<=" << ">" << ">=");
        cellWidget = new QDateEdit(this);
        qobject_cast<QDateEdit*>(cellWidget)->setCalendarPopup(true);
        break;
    case QVariant::DateTime:
        oper->addItems(QStringList() << "==" << "!=" << "<" << "<=" << ">" << ">=");
        cellWidget = new QDateTimeEdit(this);
        qobject_cast<QDateTimeEdit*>(cellWidget)->setCalendarPopup(true);
        break;
    default:
        oper->addItems(QStringList() << "==" << "!=" << "<" << "<=" << ">" << ">=");
        cellWidget = new QLineEdit(this);
        break;
    }

    if (cellWidget != NULL)
    {
        ui->tableWidget->setCellWidget(row, 3, cellWidget);
    }
}

void FilterUi::fillCombo()
{
    m_buildGrid = false;
    ui->comboLoad->clear();
    QMap<QString, QVariant> filter = Context::instance().settings()->value("filters/" + pluginId()).toMap();

    ui->comboLoad->addItem("<<empty>>", "--");
    foreach (QString key, filter.keys()) {
        ui->comboLoad->addItem(key, filter[key]);
    }
    m_buildGrid = true;
}

void FilterUi::buildGrid(const QString &expr)
{
    if (!isVisible() || !m_buildGrid)
    {
        return;
    }

    ui->tableWidget->clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        ui->tableWidget->removeRow(i);
    }
    ui->tableWidget->setRowCount(0);
    QStringList expList = expr.split(" ");
    bool newLine = true;

    for (int i = 0; i < expList.count(); i++)
    {
        if (i == 0)
        {
            addRow(false);
        }

        int rowIndex = ui->tableWidget->rowCount() - 1;

        if (newLine)
        {
            QComboBox *prop = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(rowIndex, 1));
            if (prop == NULL)
            {
                continue;
            }

            int j;
            for (j = 0; j < m_entity->metaObject()->propertyCount(); j++)
            {
                if (expList[i] == m_entity->metaObject()->property(j).name())
                {
                    break;
                }
            }
            prop->setCurrentIndex(j - 1);
            newLine = false;
        }

        if (expList[i] == "==" || expList[i] == "!=" || expList[i] == "%" || expList[i] == "<" || expList[i] == "<=" || expList[i] == ">" || expList[i] == ">=")
        {
            QComboBox *oper = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(rowIndex, 2));
            for (int j = 0; j < oper->count(); j++)
            {
                oper->setCurrentIndex(j);
                if (oper->itemText(j) == expList[i])
                {
                    break;
                }
            }
        }

        if (expList[i] == "&&")
        {
            addRow(false);
            newLine = true;
            continue;
        }

        if (expList[i] == "||")
        {
            addRow(true);
            newLine = true;
            continue;
        }

        QWidget *cellWidget = ui->tableWidget->cellWidget(rowIndex, 3);

        if (cellWidget != NULL)
        {
            cellWidget->setProperty(cellWidget->metaObject()->userProperty().name(), expList[i]);
        }
    }

}

void FilterUi::on_btnSave_clicked()
{
    SaveFilterDialog *dlg = new SaveFilterDialog(this);
    dlg->open();
    connect(dlg, &SaveFilterDialog::accepted, [this, dlg]() {
        QMap<QString, QVariant> filter = Context::instance().settings()->value("filters/" + pluginId()).toMap();
        filter[dlg->filterName()] = buildExpression();
        Context::instance().settings()->setValue("filters/" + pluginId(), QVariant::fromValue(filter));
        fillCombo();
        dlg->deleteLater();
    });
}

void FilterUi::on_comboLoad_currentIndexChanged(int index)
{
    if (ui->comboLoad->itemData(index).toString() == "--")
    {
        ui->tableWidget->clear();
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->removeRow(i);
        }
        ui->tableWidget->setRowCount(0);

        addRow(false);
    }
    else
    {
        buildGrid(ui->comboLoad->itemData(index).toString());
    }
}

void FilterUi::on_btnManage_clicked()
{
    FilterDialog *filterDialog = new FilterDialog(this);
    filterDialog->setPluginId(pluginId());
    filterDialog->open();

    connect(filterDialog, &FilterDialog::accepted, [this, filterDialog](){
        QMap<QString, QVariant> filters;
        for (int i = 0; i < filterDialog->table()->rowCount(); i++)
        {
            filters[filterDialog->table()->item(i, 0)->text()] = filterDialog->table()->item(i, 1)->text();
        }
        Context::instance().settings()->setValue("filters/" + pluginId(), QVariant::fromValue(filters));
        fillCombo();
        filterDialog->deleteLater();
    });
}
