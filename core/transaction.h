#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include "core_global.h"

class CORESHARED_EXPORT Transaction
{
public:
    Transaction();
    ~Transaction();

    void commit();

private:
    odb::transaction *m_tr;
    static bool m_inTransaction;
};

#endif // TRANSACTION_H
