#ifndef FIRSTSTARTDATA_H
#define FIRSTSTARTDATA_H

#include <QString>
#include <QSharedPointer>

class FirstStartData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dbFile READ dbFile WRITE setDbFile)
    Q_PROPERTY(QString login READ login WRITE setLogin)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(bool defaultDbPath READ defaultDbPath WRITE setDefaultDbPath)
    Q_PROPERTY(bool defaultAdmin READ defaultAdmin WRITE setDefaultAdmin)
    Q_PROPERTY(bool singleUser READ singleUser WRITE setSingleUser)

public:
    explicit FirstStartData(QObject *parent = 0);

    QString dbFile() const;
    void setDbFile(const QString &dbFile);

    QString login() const;
    void setLogin(const QString &login);

    QString password() const;
    void setPassword(const QString &password);

    bool defaultDbPath() const;
    void setDefaultDbPath(bool defaultDbPath);

    bool defaultAdmin() const;
    void setDefaultAdmin(bool defaultAdmin);

    bool singleUser() const;
    void setSingleUser(bool singleUser);

private:
    QString m_dbFile;
    QString m_login;
    QString m_password;
    bool m_defaultDbPath;
    bool m_defaultAdmin;
    bool m_singleUser;
};

typedef QSharedPointer<FirstStartData> FirstStartDataPtr;

#endif // FIRSTSTARTDATA_H
