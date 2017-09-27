#include "users.h"
#include <QFile>
#include <QJsonDocument>

Users::Users()
{
    Q_INIT_RESOURCE(rc);

    QFile f (":/users/metaData.json");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    init(d.object());
    f.close();
}

void Users::initServiceUi()
{
    m_service = new Service<User>;
    m_ui = new UsersUi;
    ((UsersUi *) m_ui)->setForm(new UserForm);
}

QIcon Users::pluginIcon()
{
    return QIcon(":/icons/usersPlugin.svg");
}
