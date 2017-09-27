#ifndef GRIDFORM_H
#define GRIDFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QLayout>
#include <QToolButton>
#include <QDesktopWidget>

#include "autoform.h"
#include "autotablemodel.h"
#include "context.h"
#include "iplugin.h"
#include "igridform.h"
#include "iservice.h"
#include "importdialog.h"
#include "csvimporter.h"
#include "importprogress.h"

template<class T>
class GridForm : public IGridForm
{

public:
    explicit GridForm(QWidget *parent = 0) :
    IGridForm(parent)
    {
        m_serviceConnected = false;
        m_permissionDenied = false;
        m_tableModel = NULL;
        m_formHandler = new DefaultFormHandler();

        m_filterUi = new FilterUi(this, new T);
        filterWidget()->layout()->addWidget(m_filterUi);
    }

    virtual ~GridForm()
    {
        if (m_form != NULL && m_form->parent() == NULL)
        {
            delete m_form;
        }

        if (m_tableModel != NULL && m_tableModel->parent() == NULL)
        {
            delete m_tableModel;
        }

        delete m_formHandler;
    }

    void setForm(AutoForm<T> *aForm) {
        Q_ASSERT(m_form == NULL);

        m_form = aForm;

        connect(m_form, &IForm::recordAdded, [this](){
            //service()->save(form()->entity());
            addRow(form()->entity());
        });
        connect(m_form, &IForm::recordUpdated, [this](){
            //service()->update(form()->entity());
            emit dataChanged();
        });
        connect(m_form, &IForm::refreshEntity, [this](){
            if (m_tableModel != NULL) {
                m_tableModel->setItemToIndex(tableView()->currentIndex(),
                                             service()->reload(m_tableModel->itemFromIndex(tableView()->currentIndex())->id()));
            }
        });
    }

    void setTableModel(AutoTableModel<T> *tableModel) {
        Q_ASSERT(m_tableModel == NULL);

        m_tableModel = tableModel;
        connect(m_filterUi, SIGNAL(applyFilter(QString)), m_tableModel, SLOT(filter(QString)));
        connect(m_filterUi, SIGNAL(restoreData()), m_tableModel, SLOT(restore()));
    }

    void setFormHandler(IFormHandler *handler) {
        delete m_formHandler;
        m_formHandler = handler;
    }

    virtual void setTranslations(const QMap<QString, QString> &translations) {
        Q_ASSERT(m_tableModel != NULL);
        m_tableModel->setTranslations(translations);
    }

public slots:
    bool fillData() {
        if (m_tableModel == NULL) {
            Q_ASSERT(false);
            return false;
        }

        m_permissionDenied = false;
        connectService();

        m_tableModel->setData(listForGrid());
        tableView()->setModel(m_tableModel);

        QList<QVariant> varList = Context::instance().settings()->value("grids/" + pluginId() + "/hide").toList();
        QList<int> hide;

        foreach (QVariant var, varList) {
            hide.append(var.toInt());
        }

        QMap<QString, QVariant> widths = Context::instance().settings()->value("grids/" + pluginId() + "/widths").toMap();
        foreach (QString key, widths.keys()) {
            tableView()->setColumnWidth(key.toInt(), widths[key].toInt());
        }

        connect(tableView()->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(widthChanged(int,int,int)));
        hideColumns(hide);
        enableButtons();

        connect(tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, [this](const QModelIndex &current, const QModelIndex &){
            currentIndexChanged(current);
        });

        return !m_permissionDenied;
    }

private:
    AutoTableModel<T> *m_tableModel;
    IFormHandler *m_formHandler;

    Service<T> *service() {
        IPlugin *plugin = Context::instance().plugin(pluginId());
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

    AutoForm<T> *form() {
        return (AutoForm<T>*)m_form;
    }

    void connectService() {
        if (!m_serviceConnected)
        {
            connect(service(), &IService::dbErrorRead, [this](QString msg) {
               QMessageBox::critical(this, tr("Database error"), tr(msg.toStdString().c_str()));
            });
            connect(service(), &IService::dbErrorDelete, [this](QString msg) {
               QMessageBox::critical(this, tr("Database error"), tr(msg.toStdString().c_str()));
            });
            this->connect(service(), &IService::permissionDenied, [this](QString permission) {
                if (permission == PERM_READ || permission == PERM_DELETE) {
                    QMessageBox::critical(this, "Permission denied", permission .toStdString().c_str());
                    m_permissionDenied = true;
                }
            });

            m_serviceConnected = true;
        }
    }

    bool m_serviceConnected;
    bool m_permissionDenied;

private slots:

    // IGridForm interface
protected:
    virtual void handleNewRecord() override
    {
        if (!checkPermAdd())
        {
            return;
        }

        if (m_form == NULL)
        {
            Q_ASSERT(false);
            return;
        }

        form()->setEntity(QSharedPointer<T>(new T()));
        form()->setNewRec(true);
        m_formHandler->showForm(m_form);
    }

    virtual void handleEditRecord() override
    {
        if (!checkPermEdit())
        {
            return;
        }

        if (m_form == NULL || m_tableModel == NULL || tableView()->currentIndex().row() < 0)
        {
            Q_ASSERT(false);
            return;
        }

        form()->setEntity(m_tableModel->itemFromIndex(tableView()->currentIndex()));
        form()->setNewRec(false);
        m_formHandler->showForm(m_form);
    }

    void handleDeleteRecord() override
    {
        if (!checkPermDelete())
        {
            return;
        }

        m_permissionDenied = false;
        connectService();
        if (m_form == NULL || m_tableModel == NULL || tableView()->currentIndex().row() < 0)
        {
            Q_ASSERT(false);
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Delete record"), tr("Realy delete this record?"), QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QSharedPointer<T> entity = m_tableModel->itemFromIndex(tableView()->currentIndex());
            doDelete(entity);

            if (!m_permissionDenied)
            {
                m_tableModel->removeRowAt(tableView()->currentIndex());
                emit dataChanged();
            }
        }
    }

    bool checkPermAdd()
    {
        PermissionEvaluator permEv;
        if (!permEv.hasPermission(pluginId(), PERM_ADD))
        {
            QMessageBox::critical(this, tr("Permission denied"), tr("You don't have permission to add new record."));
            return false;
        }

        return true;
    }

    bool checkPermEdit()
    {
        PermissionEvaluator permEv;
        if (!permEv.hasPermission(pluginId(), PERM_EDIT))
        {
            QMessageBox::critical(this, tr("Permission denied"), tr("You don't have permission to edit record."));
            return false;
        }

        return true;
    }

    bool checkPermDelete()
    {
        PermissionEvaluator permEv;
        if (!permEv.hasPermission(pluginId(), PERM_DELETE))
        {
            QMessageBox::critical(this, tr("Permission denied"), tr("You don't have permission to delete record."));
            return false;
        }

        return true;
    }

    virtual int currentRecordId()
    {
        if (tableView()->currentIndex().isValid())
        {
            return m_tableModel->itemFromIndex(tableView()->currentIndex())->id();
        }

        return 0;
    }

    QSharedPointer<T> currentEntity()
    {
        if (tableView()->currentIndex().isValid())
        {
            return m_tableModel->itemFromIndex(tableView()->currentIndex());
        }

        return QSharedPointer<T>();
    }

    virtual void doDelete(QSharedPointer<T> entity)
    {
        service()->erase(entity);
    }

    virtual QList<QSharedPointer<T> > listForGrid()
    {
        return service()->all();
    }

    void addRow(QSharedPointer<T> entity)
    {
        m_tableModel->addRow(entity);
        emit dataChanged();
    }

    void showImportButton()
    {
        QHBoxLayout *tbLayout = qobject_cast<QHBoxLayout*>(this->toolbar()->layout());

        if (tbLayout != NULL)
        {
            QToolButton *btnImport = new QToolButton(this->toolbar());
            btnImport->setIcon(QIcon(":/icons/import.svg"));
            btnImport->setAutoRaise(true);
            btnImport->setIconSize(QSize(24, 24));
            btnImport->setToolTip(tr("Import"));
            tbLayout->insertWidget(tbLayout->count() - 1, btnImport);

            connect(btnImport, &QToolButton::clicked, [this](){
                ImportDialog *dlg = new ImportDialog(this);
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                dlg->show();

                /*connect(dlg, &QDialog::accepted, [this, dlg](){
                    T dataObj;
                    CsvImporter importer(dataObj.metaObject());

                    importer.setImportFile(dlg->fileName());
                    importer.setSeparator(dlg->separator());

                    ImportProgress *progress = new ImportProgress();
                    progress->move(QApplication::desktop()->screen()->rect().center() - progress->rect().center());
                    progress->setWindowModality(Qt::ApplicationModal);
                    progress->show();

                    service()->importData(&importer, progress);
                });*/
            });
        }
    }
};

#endif // GRIDFORM_H
