#include "roles.h"
#include "rolesui.h"
#include "rolesform.h"

#include <QFile>
#include <QJsonDocument>

Roles::Roles()
{
    Q_INIT_RESOURCE(rc);

    QFile f (":/roles/metaData.json");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    init(d.object());
    f.close();
}

void Roles::initServiceUi()
{
    m_service = new Service<Role>();
    m_ui = new RolesUi();
    ((RolesUi*)m_ui)->setForm(new RolesForm());
}

QIcon Roles::pluginIcon()
{
    return QIcon(":/icons/rolesPlugin.svg");
}
