#ifndef AUTOFORM_H
#define AUTOFORM_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>

#include "service.h"
#include "iservice.h"
#include "iplugin.h"
#include "formbinder.h"

#include "combodata.h"

template <class T>
class AutoForm : public FormBinder<T>
{
public:
    explicit AutoForm(QWidget *parent = 0) {
        this->setParent(parent);
        m_serviceConnected = false;
        m_saved = false;
    }

    virtual ~AutoForm() { }

    void setNewRec(bool isNew) {
        this->m_newRec = isNew;
    }

public slots:
    bool saveRecord() {
        if (!this->bindToData())
        {
            return false;
        }

        if (!m_serviceConnected)
        {
            this->connect(service(), &IService::dbError, [this](QString msg) {
                QMessageBox::critical(this, this->tr("Database error"), msg.toStdString().c_str());
                m_saved = false;
            });
            this->connect(service(), &IService::permissionDenied, [this](QString permission) {
                if (permission != PERM_DELETE) {
                    QMessageBox::critical(this, this->tr("Permission denied"), permission.toStdString().c_str());
                    m_saved = false;
                }
            });
            this->connect(service(), &IService::dataChanged, [this]() {
                m_saved = true;
            });
            m_serviceConnected = true;
        }

        if (this->m_newRec) {
            service()->save(this->entity());
            if (m_saved)
            {
                emit this->recordAdded();
            }
        } else {
            service()->update(this->entity());
            if (m_saved)
            {
                emit this->recordUpdated();
            }
        }

        return m_saved;
    }

private:
    Service<T> *service() {
        IPlugin *plugin = Context::instance().plugin(this->pluginId());
        if (plugin == NULL) {
            Q_ASSERT(false);
            return NULL;
        }

        Service<T> *service = plugin->service<T>();
        if (service == NULL) {
            Q_ASSERT(false);
            return NULL;
        }

        return service;
    }

    bool m_serviceConnected;
    bool m_saved;
};

#endif // AUTOFORM_H
