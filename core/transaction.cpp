#include "transaction.h"

#include "context.h"

bool Transaction::m_inTransaction = false;

Transaction::Transaction()
{
    if (!Transaction::m_inTransaction)
    {
        m_tr = new odb::transaction(Context::instance().db()->begin());
#ifdef _DEBUG
        m_tr->tracer(odb::stderr_tracer);
#endif
        Transaction::m_inTransaction = true;
    }
    else
    {
        m_tr = NULL;
    }
}

Transaction::~Transaction()
{
    if (m_tr != NULL)
    {
        delete m_tr;
        Transaction::m_inTransaction = false;
    }
}

void Transaction::commit()
{
    if (m_tr != NULL)
    {
        m_tr->commit();
    }
}

