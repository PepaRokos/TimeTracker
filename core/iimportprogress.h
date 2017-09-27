#ifndef IIMPORTPROGRESS_H
#define IIMPORTPROGRESS_H

#include "core_global.h"

class CORESHARED_EXPORT IImportProgress
{
public:
    virtual void updateProgress(int currentPos) = 0;
    virtual bool terminate() = 0;
};

#endif // IIMPORTPROGRESS_H
