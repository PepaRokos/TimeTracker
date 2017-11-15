#include "addressbook.h"

#include "addressgrid.h"
#include "addressform.h"
#include "addressservice.h"

AddressBook::AddressBook()
{
}

void AddressBook::initServiceUi()
{
    m_ui = new AddressGrid();
    ((AddressGrid*)m_ui)->setForm(new AddressForm());
    m_service = new AddressService();
}

QIcon AddressBook::pluginIcon()
{
    return QIcon(":/icons/addressbook_48x48.png");
}
