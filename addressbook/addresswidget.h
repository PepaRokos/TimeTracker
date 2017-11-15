#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include <QWidget>
#include <core.h>
#include "iaddressable.h"
#include "addrwidgetentity.h"
#include "addressbook_global.h"

namespace Ui {
class AddressWidget;
}

class ADDRESSBOOKSHARED_EXPORT AddressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddressWidget(QWidget *parent = 0);
    ~AddressWidget();

    void bindToData();
    void setTargetEntity(IAddressablePtr entity);
    IAddressablePtr targetEntity();
    bool hasAddress();

private slots:
    void on_groupBox_clicked(bool checked);

    void on_addressId_currentIndexChanged(int index);

    void on_checkNewAddressBox_clicked(bool checked);

signals:
    void addressChecked();

private:
    Ui::AddressWidget *ui;
    ObjectBinder m_binder;
    AddrWidgetEntityPtr m_entity;
    IAddressablePtr m_targetEntity;

    void bindToUi();
    void enableEdit(bool customAddr);
    void initEntity();
};

#endif // ADDRESSWIDGET_H
