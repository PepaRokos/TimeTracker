#include "defaultformhandler.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

DefaultFormHandler::DefaultFormHandler()
{
    m_dialog = new FormDialog();
}

DefaultFormHandler::~DefaultFormHandler()
{
    delete m_dialog;
}

void DefaultFormHandler::showForm(IForm *formWidget)
{
    m_dialog->setForm(formWidget);
    m_dialog->setModal(true);
    m_dialog->move(QApplication::desktop()->screen()->rect().center() - m_dialog->rect().center());
    m_dialog->show();
}

