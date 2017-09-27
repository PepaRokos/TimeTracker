#include "core-odb.hxx"
#include "permissionservice.h"
#include <QCryptographicHash>

typedef odb::query<Permission> permQuery;
typedef odb::result<Permission> permResult;

PermissionService::PermissionService()
{
}

PermissionService::~PermissionService()
{
}

QList<QSharedPointer<Permission> > PermissionService::forPlugin(const QString &pluginId)
{
    Transaction tr;
    odb::database *db = Context::instance().db();
    permQuery q(permQuery::pluginId == pluginId);
    permResult result = db->query<Permission>(q);

    QList<QSharedPointer<Permission> > ret;
    for (permResult::iterator it = result.begin(); it != result.end(); it++)
    {
        ret.append(it.load());
    }

    tr.commit();
    return ret;
}

QSharedPointer<Permission> PermissionService::forNameAndPlugin(const QString &name, const QString &pluginId)
{
    Transaction tr;
    odb::database *db = Context::instance().db();
    permQuery q(permQuery::pluginId == pluginId && permQuery::permissionName == name);
    QSharedPointer<Permission> p = db->query_one<Permission>(q);

    tr.commit();
    return p;
}

bool PermissionService::checkLogin(const QString &login, const QString &password)
{

    QSharedPointer<User> user = loadUser(login);
    if (user.data())
    {
        return user->password() == encryptPassword(password) && user->active();
    }

    return false;
}

QSharedPointer<User> PermissionService::loadUser(const QString &login)
{
    odb::database *db = Context::instance().db();

    Transaction tr;
    return db->query_one<User>("login = " + odb::query<User>::_ref(login));
}

void PermissionService::checkForAdmin()
{
    odb::database *db = Context::instance().db();

    Transaction tr;
    odb::query<User> q(odb::query<User>::isAdmin == true);
    odb::result<User> r = db->query<User>(q);

    if (r.empty())
    {
        QSharedPointer<User> admin(new User);
        admin->setLogin("admin");
        admin->setName("Administrator");
        admin->setIsAdmin(true);
        admin->setPassword(encryptPassword("admin"));
        admin->setActive(true);

        db->persist(admin);
    }

    tr.commit();
}

QString PermissionService::encryptPassword(const QString &plainPasswd)
{
    return QString(QCryptographicHash::hash(plainPasswd.toUtf8(),QCryptographicHash::Sha256).toBase64());
}

