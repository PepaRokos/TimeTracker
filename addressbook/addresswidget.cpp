#include "addresswidget.h"
#include "ui_addresswidget.h"

#include "addressservice.h"
#include "addressbook-odb.hxx"

AddressWidget::AddressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddressWidget)
{
    ui->setupUi(this);

    m_binder.registerBinding(ui->company);
    m_binder.registerBinding(ui->ic);
    m_binder.registerBinding(ui->dic);
    m_binder.registerBinding(ui->street);
    m_binder.registerBinding(ui->houseNumber);
    m_binder.registerBinding(ui->city);
    m_binder.registerBinding(ui->zipCode);

    m_entity = AddrWidgetEntityPtr(new AddrWidgetEntity);
}

AddressWidget::~AddressWidget()
{
    delete ui;
}

void AddressWidget::bindToUi()
{
    AddressService srv;
    QList<AddressPtr> addresses = srv.all("ORDER BY company");

    m_binder.registerBinding(ui->addressId, ComboData::createComboData(addresses));
    m_binder.setData(m_entity.data());
    m_binder.bindToUi();
}

void AddressWidget::bindToData()
{
    if (m_targetEntity == nullptr)
    {
        return;
    }

    m_binder.bindToData();

    if (ui->checkNewAddressBox->isChecked())
    {
        m_entity->setAddressIdPtr(AddressPtr());
    }

    AddressService srv;
    srv.copyAddress(m_entity.data(), m_targetEntity.data());
}

void AddressWidget::setTargetEntity(IAddressablePtr entity)
{
    m_targetEntity = entity;

    QObject *qEntity = dynamic_cast<QObject*>(entity.data());
    if (qEntity != nullptr)
    {
        ui->groupBox->setChecked(true);
        AddressService srv;

        srv.copyAddress(m_targetEntity.data(), m_entity.data());
        bindToUi();

        ui->checkNewAddressBox->setChecked(m_targetEntity->addressIdPtr().isNull());
        enableEdit(m_targetEntity->addressIdPtr().isNull());
    }
    else
    {
        ui->groupBox->setChecked(false);
    }
}

IAddressablePtr AddressWidget::targetEntity()
{
    return m_targetEntity;
}

bool AddressWidget::hasAddress()
{
    return ui->groupBox->isChecked();
}

void AddressWidget::enableEdit(bool customAddr)
{
    ui->addressId->setEnabled(!customAddr);
    ui->company->setReadOnly(!customAddr);
    ui->ic->setReadOnly(!customAddr);
    ui->dic->setReadOnly(!customAddr);
    ui->street->setReadOnly(!customAddr);
    ui->houseNumber->setReadOnly(!customAddr);
    ui->city->setReadOnly(!customAddr);
    ui->zipCode->setReadOnly(!customAddr);
}

void AddressWidget::initEntity()
{
    AddressService srv;
    QList<AddressPtr> addresses = srv.all("ORDER BY company");

    if (!addresses.isEmpty())
    {
        m_entity->setAddressIdPtr(addresses[0]);
        ui->checkNewAddressBox->setChecked(false);
        enableEdit(false);
    }
    else
    {
        ui->checkNewAddressBox->setChecked(true);
        ui->checkNewAddressBox->setEnabled(false);
        enableEdit(true);
    }
}

void AddressWidget::on_groupBox_clicked(bool checked)
{
    if (checked)
    {
        if (m_targetEntity.isNull())
        {
            m_targetEntity = AddrWidgetEntityPtr(new AddrWidgetEntity);
        }

        initEntity();
        bindToUi();

        on_addressId_currentIndexChanged(0);
        emit addressChecked();
    }
}

void AddressWidget::on_addressId_currentIndexChanged(int)
{
    AddressService addrSrv;
    m_binder.bindToData();
    addrSrv.copyAddress(m_entity->addressIdPtr(), m_entity);
    m_binder.bindToUi();
}

void AddressWidget::on_checkNewAddressBox_clicked(bool checked)
{
    if (checked)
    {
        m_entity->setAddressIdPtr(AddressPtr());
        enableEdit(true);
    }
    else
    {
        AddressService addrSrv;
        QList<AddressPtr> addresses = addrSrv.all("ORDER BY company");
        m_entity->setAddressIdPtr(addresses[0]);

        enableEdit(false);
        m_binder.bindToData();
        addrSrv.copyAddress(m_entity->addressIdPtr(), m_entity);
        m_binder.bindToUi();
    }
}
