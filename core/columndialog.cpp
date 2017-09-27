#include "columndialog.h"
#include "ui_columndialog.h"

#include <QTableWidgetItem>
#include <QHeaderView>

ColumnDialog::ColumnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColumnDialog)
{
    ui->setupUi(this);
}

ColumnDialog::~ColumnDialog()
{
    delete ui;
}

void ColumnDialog::setTable(QTableView *table)
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Column"));
    ui->tableWidget->setRowCount(table->model()->columnCount());
    for (int i = 0; i < table->model()->columnCount(); i++)
    {
        QVariant data = table->model()->headerData(i, Qt::Horizontal);
        QTableWidgetItem *item = new QTableWidgetItem(data.toString());

        if (table->isColumnHidden(i))
        {
            item->setCheckState(Qt::Unchecked);
        }
        else
        {
            item->setCheckState(Qt::Checked);
        }
        ui->tableWidget->setItem(i, 0, item);
    }

    QHeaderView *horzHdr = ui->tableWidget->horizontalHeader();
    horzHdr->setStretchLastSection(true);
}

QList<int> ColumnDialog::columnsToHide()
{
    QList<int> list;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Unchecked)
        {
            list.append(i);
        }
    }

    return list;
}

