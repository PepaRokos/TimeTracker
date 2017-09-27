#ifndef ROLESFORM_H
#define ROLESFORM_H

#include <QWidget>
#include "autoform.h"
#include "data/core-data.h"
#include "core-odb.hxx"

namespace Ui {
class RolesForm;
}

class RolesForm : public AutoForm<Role>
{
    Q_OBJECT

public:
    explicit RolesForm(QWidget *parent = 0);
    ~RolesForm();

private:
    Ui::RolesForm *ui;

    // AutoForm interface
protected:
    virtual void bindOtherToUi() override;
    virtual bool bindOtherToData() override;
};

#endif // ROLESFORM_H
