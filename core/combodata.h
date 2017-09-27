#ifndef COMBODATA_H
#define COMBODATA_H

#include <QVariant>
#include <QSharedDataPointer>

#include "core_global.h"
#include "data/comboitem.h"

class CORESHARED_EXPORT ComboData
{
public:
    ComboData(const QVariant &index, const QString &label);
    ComboData(const QSharedPointer<QObject> &index);
    ~ComboData();

    QVariant index() const;
    void setIndex(const QVariant &index);

    QString label() const;
    void setLabel(const QString &label);

    template<class T>
    static QList<ComboData> createComboData(QList<QSharedPointer<T> > list) {
        QList<ComboData> data;
        foreach (QSharedPointer<T> item, list) {
            QSharedPointer<QObject> qObj = qSharedPointerDynamicCast<QObject, T>(item);
            if (!qObj.isNull())
            {
                data << ComboData(qObj);
            }
        }

        return data;
    }

private:
    QVariant m_index;
    QString m_label;
};

#endif // COMBODATA_H
