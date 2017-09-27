#include "iform.h"

IForm::IForm(QWidget *parent) : QWidget(parent)
{   
    m_newRec = false;
}

IForm::~IForm()
{
}

QString IForm::pluginId() const
{
    return m_pluginId;
}

void IForm::setPluginId(const QString &pluginId)
{
    m_pluginId = pluginId;
}

void IForm::refresh()
{
    if (!m_newRec)
    {
        emit refreshEntity();
    }
}

