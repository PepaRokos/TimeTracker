#ifndef FORMBINDER_H
#define FORMBINDER_H

#include <QSharedPointer>
#include <QComboBox>
#include <QWidget>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QVariant>

#include "combodata.h"
#include "ivalidator.h"
#include "iform.h"
#include "objectbinder.h"

#include <QDecDouble.hh>

template<class T>
class FormBinder : public IForm
{
public:

    explicit FormBinder(QWidget *parent = NULL) : IForm(parent) {
        connect(&m_binder, &ObjectBinder::validationError, [this](QString msg){
            emit this->validationError(msg);
        });
    }

    virtual ~FormBinder() {

    }

    void registerBinding(QWidget *widget) {
        m_binder.registerBinding(widget);
    }

    void registerBinding(QComboBox *combo, const QList<ComboData> &values) {
        m_binder.registerBinding(combo, values);
    }

    void registerValidator(IValidator *validator) {
        m_binder.registerValidator(validator);
    }

    void setEntity(QSharedPointer<T> entity) {
        m_entity = entity;
        m_binder.setData(m_entity.data());
        bindToUi();
    }

    QSharedPointer<T> entity() {
        return m_entity;
    }

protected:
    QSharedPointer<T> m_entity;

    virtual void bindOtherToUi() {}
    virtual bool bindOtherToData() { return true; }
    virtual void registerCombos() {}

    void bindToUi() {
        registerCombos();
        m_binder.bindToUi();
        bindOtherToUi();
    }

    bool bindToData() {
        return m_binder.bindToData() && bindOtherToData();
    }

private:
    ObjectBinder m_binder;
};

#endif // FORMBINDER_H
