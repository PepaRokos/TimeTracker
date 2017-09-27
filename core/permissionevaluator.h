#ifndef PERMISSIONEVALUATOR_H
#define PERMISSIONEVALUATOR_H

#include <QObject>
#include <QString>

#include "core_global.h"

class CORESHARED_EXPORT PermissionEvaluator : public QObject
{
    Q_OBJECT

public:
    explicit PermissionEvaluator(QObject *parent = NULL);
    ~PermissionEvaluator();

    bool hasPermission(const QString &pluginId, const QString &permission);

signals:
    void permissionDenied(QString permission);
};

#endif // PERMISSIONEVALUATOR_H
