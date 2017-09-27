#include "filterdialog.h"
#include "ui_filterdialog.h"

#include <QMap>
#include <QTableWidgetItem>
#include <QToolButton>

#include "context.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

QString FilterDialog::pluginId() const
{
    return m_pluginId;
}

void FilterDialog::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;
    fillTable();
}

QTableWidget *FilterDialog::table()
{
    return ui->tableWidget;
}

void FilterDialog::fillTable()
{
    ui->tableWidget->clear();
    QMap<QString, QVariant> filters = Context::instance().settings()->value("filters/" + pluginId()).toMap();

    int row = 0;
    ui->tableWidget->setRowCount(filters.keys().size());
    foreach (QString name, filters.keys()) {
        QTableWidgetItem *itemName = new QTableWidgetItem(name);
        ui->tableWidget->setItem(row, 0, itemName);
        QTableWidgetItem *itemFilter = new QTableWidgetItem(filters[name].toString());
        ui->tableWidget->setItem(row, 1, itemFilter);

        QToolButton *btnRemove = new QToolButton();
        btnRemove->setText("Remove");
        ui->tableWidget->setCellWidget(row, 2, btnRemove);
        connect(btnRemove, &QToolButton::clicked, [this, btnRemove](){
            int rowToDel = ui->tableWidget->rowAt(btnRemove->y());
            ui->tableWidget->removeRow(rowToDel);
        });

        row++;
    }

    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Filter") << "");
}
