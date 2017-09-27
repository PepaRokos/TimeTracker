#include "objectbinder.h"
#include <QDecDouble.hh>

ObjectBinder::ObjectBinder(QObject *parent)
    :QObject(parent)
{
    m_data = NULL;
}

void ObjectBinder::registerBinding(QWidget *widget) {
    if (!m_bindWidgets.contains(widget)) {
        m_bindWidgets.append(widget);
    }
}

void ObjectBinder::registerBinding(QComboBox *combo, const QList<ComboData> &values) {
    m_bindCombos[combo] = values;
}

void ObjectBinder::registerValidator(IValidator *validator) {
    m_validators.append(validator);
}

void ObjectBinder::setData(QObject *data)
{
    m_data = data;
}

void ObjectBinder::bindToUi() {
    foreach (QWidget *widget, m_bindWidgets) {
        const char* prop = widget->metaObject()->userProperty().name();
        QVariant value = m_data->property(widget->objectName().toStdString().c_str());
        if (value.canConvert<QDecDouble>())
        {
            widget->setProperty(prop, value.value<QDecDouble>().toString());
        }
        else
        {
            widget->setProperty(prop, value);
        }
    }

    foreach (QComboBox *combo, m_bindCombos.keys()) {
        int idx = 0;
        QVariant field = m_data->property(combo->objectName().toStdString().c_str());

        combo->clear();
        for (int i = 0; i < m_bindCombos[combo].size(); i++) {
            ComboData data = m_bindCombos[combo][i];
            combo->addItem(data.label(), data.index());

            if (data.index().canConvert<QObject*>()) {
                ComboItem* ci = qobject_cast<ComboItem*>(data.index().value<QObject*>());
                ComboItem* ciField = qobject_cast<ComboItem*>(field.value<QObject*>());
                if (ci->eq(ciField)) {
                    idx = i;
                }
            }
            else if (field == data.index()) {
                idx = i;
            }
        }

        combo->setCurrentIndex(idx);
    }
}

bool ObjectBinder::bindToData() {
    foreach (IValidator *val, m_validators) {
        if (!val->validate()) {
            emit validationError(val->errMessage());
            return false;
        }
    }

    foreach (QWidget *widget, m_bindWidgets) {
        const char* prop = widget->metaObject()->userProperty().name();

        QVariant val = widget->property(prop);
        if (m_data->property(widget->objectName().toStdString().c_str()).canConvert<QDecDouble>())
        {
            QDecDouble dec(val.toDouble());
            val = QVariant::fromValue(dec);
        }
        m_data->setProperty(widget->objectName().toStdString().c_str(), val);
    }

    foreach (QComboBox *combo, m_bindCombos.keys()) {
        m_data->setProperty(combo->objectName().toStdString().c_str(), combo->currentData());
    }

    return true;
}
