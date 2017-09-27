#include "application.h"

Application::Application(int &argc, char **argv)
    :QApplication(argc, argv)
{
    m_single = new QSharedMemory("ShredMemoryForOneInstanceOfTimeTrackerApp", this);
}

Application::~Application()
{
    if (m_single->isAttached())
    {
        m_single->detach();
    }
}

bool Application::lock()
{
    if (m_single->attach(QSharedMemory::ReadOnly))
    {
        m_single->detach();
        return false;
    }

    if (m_single->create(1))
    {
        return true;
    }

    return false;
}
