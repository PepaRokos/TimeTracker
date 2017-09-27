#ifndef IMPORTPROGRESS_H
#define IMPORTPROGRESS_H

#include <QWidget>
#include "iimportprogress.h"

#include "core_global.h"

namespace Ui {
class ImportProgress;
}

class CORESHARED_EXPORT ImportProgress : public QWidget, public IImportProgress
{
    Q_OBJECT

public:
    explicit ImportProgress(QWidget *parent = 0);
    ~ImportProgress();

private slots:
    void on_btnCancel_clicked();

private:
    Ui::ImportProgress *ui;
    bool m_terminate;

    // IImportProgress interface
public:
    void updateProgress(int currentPos);
    bool terminate();
};

#endif // IMPORTPROGRESS_H
