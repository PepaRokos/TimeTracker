#include "formdialog.h"
#include "ui_formdialog.h"
#include <QMessageBox>
#include "context.h"
#include "iplugin.h"

FormDialog::FormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormDialog)
{
    ui->setupUi(this);
    m_formSet = false;
    m_form = NULL;
}

FormDialog::~FormDialog()
{
    delete ui;
}

void FormDialog::setForm(IForm *formWidget)
{
    if (m_form == NULL)
    {
        ui->verticalLayout->addWidget(formWidget);
        m_form = formWidget;
        connect(m_form, SIGNAL(validationError(QString)), this, SLOT(onValidationError(QString)));
        setGeometry(formWidget->geometry());
        ui->labelName->setText(Context::instance().plugin(formWidget->pluginId())->pluginName());
        ui->labelIcon->setPixmap(Context::instance().plugin(formWidget->pluginId())->pluginIcon().pixmap(QSize(36, 36)));
    }
}

void FormDialog::onValidationError(const QString &message)
{
    QMessageBox::critical(this, tr("Validation error"), tr(message.toStdString().c_str()));
}

void FormDialog::accept()
{
    if (m_form->saveRecord())
    {
        QDialog::accept();
    }
}

void FormDialog::reject()
{
    m_form->refresh();
    QDialog::reject();
}
