#include "rolesform.h"
#include "ui_rolesform.h"
#include "iplugin.h"
#include "permissionservice.h"

#include <QTreeWidgetItem>

RolesForm::RolesForm(QWidget *parent) :
    AutoForm<Role>(parent),
    ui(new Ui::RolesForm)
{
    ui->setupUi(this);

    registerBinding(ui->active);
    registerBinding(ui->name);
}

RolesForm::~RolesForm()
{
    delete ui;
}

void RolesForm::bindOtherToUi()
{
    ui->treePerms->clear();
    QList<QSharedPointer<Permission> > perms = entity()->listPermissions();

    foreach (IPlugin *plugin, Context::instance().plugins()) {
        if (plugin->pluginId() != "CORE")
        {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, plugin->pluginName());
            item->setData(0, Qt::UserRole, plugin->pluginId());

            foreach (QString perm, Context::instance().defaultPerms()) {
                QTreeWidgetItem *permItem = new QTreeWidgetItem();
                permItem->setText(0, tr(perm.toStdString().c_str()));
                permItem->setData(0, Qt::UserRole, perm);
                QList<QSharedPointer<Permission> >::iterator it = std::find_if(ALL(perms), [&perm, plugin](QSharedPointer<Permission> p){ return p->permissionName() == perm
                        && p->pluginId() == plugin->pluginId(); });
                permItem->setCheckState(0, it != perms.end() ? Qt::Checked : Qt::Unchecked);
                item->addChild(permItem);
            }
            ui->treePerms->addTopLevelItem(item);
        }
    }
}

bool RolesForm::bindOtherToData()
{
    PermissionService permService;

    entity()->clearPermissions();
    for (int i = 0; i < ui->treePerms->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treePerms->topLevelItem(i);

        for (int j = 0; j < item->childCount(); j++)
        {
            QTreeWidgetItem *permItem = item->child(j);
            if (permItem->checkState(0) == Qt::Checked)
            {
                QSharedPointer<Permission> perm = permService.forNameAndPlugin(permItem->data(0, Qt::UserRole).toString(), item->data(0, Qt::UserRole).toString());
                perm->addRole(entity());
                entity()->addPermission(perm);
            }
        }
    }

    return true;
}
