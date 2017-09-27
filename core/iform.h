#ifndef IFORM_H
#define IFORM_H

#include <QWidget>
#include <QString>
#include <QSharedPointer>
#include <QObject>

#include "core_global.h"

class CORESHARED_EXPORT IForm : public QWidget
{
    Q_OBJECT

public:
    explicit IForm(QWidget *parent = 0);
    virtual ~IForm();

    QString pluginId() const;
    void setPluginId(const QString &pluginId);
    virtual void loadEntity() {}

signals:
    void recordAdded();
    void recordUpdated();
    void validationError(const QString &errMessage);
    void refreshEntity();

public slots:
    virtual bool saveRecord() = 0;
    void refresh();

private:
    QString m_pluginId;

protected:
    bool m_newRec;
};

#endif // IFORM_H
