#ifndef IIMPORTER_H
#define IIMPORTER_H

#include <QMetaObject>
#include <QObject>
#include <QSharedPointer>
#include "core_global.h"

class CORESHARED_EXPORT IImporter
{
public:
    explicit IImporter(const QMetaObject *metaObject) { m_metaObject = metaObject; }

    virtual void setImportFile(const QString &fileName) = 0;
    virtual int recordCount() = 0;
    virtual QSharedPointer<QObject> nextRecord() = 0;
    virtual bool isError() = 0;

protected:
    const QMetaObject *m_metaObject;
};

#endif // IIMPORTER_H
