#ifndef ISERVICE_H
#define ISERVICE_H

#include <QObject>
#include <QString>

#include "core_global.h"

class CORESHARED_EXPORT IService : public QObject
{
    Q_OBJECT

public:
    explicit IService(QObject *parent = 0);
    virtual ~IService();

    void setPluginId(const QString &pluginId);

signals:
    void dbError(QString errMsg);
    void dbErrorRead(QString errMsg);
    void dbErrorInsert(QString errMsg);
    void dbErrorUpdate(QString errMsg);
    void dbErrorDelete(QString errMsg);
    void dataChanged();
    void updateDenied();
    void readDenied();
    void permissionDenied(QString permission);

public slots:

protected:
    QString m_pluginId;
};

#endif // ISERVICE_H
