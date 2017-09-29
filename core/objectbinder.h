#ifndef OBJECTBINDER_H
#define OBJECTBINDER_H

#include <QList>
#include <QWidget>
#include <QComboBox>
#include <QObject>
#include <QMetaProperty>
#include "ivalidator.h"
#include "combodata.h"
#include "core_global.h"

class CORESHARED_EXPORT ObjectBinder : public QObject
{
    Q_OBJECT

public:
    explicit ObjectBinder(QObject *parent = NULL);

    void registerBinding(QWidget *widget);
    void registerBinding(QComboBox *combo, const QList<ComboData> &values);
    void registerValidator(IValidator *validator);
    void setData(QObject *data);
    void bindToUi();
    bool bindToData();

signals:
    void validationError(QString msg);

private:
    QList<QWidget*> m_bindWidgets;
    QHash<QComboBox*, QList<ComboData> > m_bindCombos;
    QList<IValidatorPtr> m_validators;
    QObject *m_data;
};

#endif // OBJECTBINDER_H
