#include "trackerform.h"
#include "ui_trackerform.h"

#include "clientdialog.h"
#include "datebeforevalidator.h"

#include <emptystringvalidator.h>
#include <addressservice.h>

TrackerForm::TrackerForm(QWidget *parent) :
    AutoForm<Project>(parent),
    ui(new Ui::TrackerForm)
{
    ui->setupUi(this);

    registerBinding(ui->name);
    registerBinding(ui->start);
    registerBinding(ui->dueTo);
    registerBinding(ui->pricePerHour);

    IValidator *dateValidator = new DateBeforeValidator(ui->dueTo, tr("Due to date must be after start date."), ui->start);
    registerValidator(dateValidator);
    IValidator *nameValidator = new EmptyStringValidator(ui->name, tr("Project name cannot by empty."));
    registerValidator(nameValidator);

    m_addrWidget = new AddressWidget(this);
    ui->widgetAddr->layout()->addWidget(m_addrWidget);

    connect(m_addrWidget, &AddressWidget::addressChecked, [this](){
        if (entity()->client().isNull())
        {
            AddressService srv;
            ClientPtr client = ClientPtr(new Client());
            srv.copyAddress(m_addrWidget->targetEntity().data(), client.data());
            entity()->setClient(client);
            m_addrWidget->setTargetEntity(client);
            m_newClient = true;
        }
    });

    m_newClient = false;
}

TrackerForm::~TrackerForm()
{
    delete ui;
}

void TrackerForm::bindOtherToUi()
{
    ProjectPtr project = entity();

    if (!project->client().isNull())
    {
        m_addrWidget->setTargetEntity(qSharedPointerDynamicCast<IAddressable, QObject>(project->client()));
    }
    else if (m_newRec)
    {
        ClientPtr client = ClientPtr(new Client());
        entity()->setClient(client);

        m_addrWidget->setTargetEntity(client);
        m_newClient = true;
    }
    else
    {
        m_addrWidget->setTargetEntity(ClientPtr());
    }
}

bool TrackerForm::bindOtherToData()
{
    m_addrWidget->bindToData();

    if (m_addrWidget->hasAddress())
    {
        Service<Client> srvClient;

        if (m_newClient)
        {
            srvClient.save(qSharedPointerDynamicCast<Client, QObject>(entity()->client()));
        }
        else
        {
            srvClient.update(qSharedPointerDynamicCast<Client, QObject>(entity()->client()));
        }
    }
    else
    {
        entity()->setClient(ClientPtr());
    }

    return true;
}

