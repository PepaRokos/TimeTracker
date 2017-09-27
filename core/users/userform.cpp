#include "userform.h"
#include "ui_userform.h"

#include <QTableWidgetItem>
#include <QHeaderView>
#include "../data/core-data.h"
#include "../service.h"
#include "../permissionservice.h"
#include "../emptystringvalidator.h"
#include "../samestringvalidator.h"

UserForm::UserForm(QWidget *parent) :
    AutoForm<User>(parent),
    ui(new Ui::UserForm)
{
    m_passChanged = false;
    ui->setupUi(this);
    registerBinding(ui->login);
    registerBinding(ui->password);
    registerBinding(ui->name);
    registerBinding(ui->isAdmin);
    registerBinding(ui->active);
    EmptyStringValidator * esv_login = new EmptyStringValidator(ui->login,"Enter Login Name");
    registerValidator(esv_login);
    EmptyStringValidator * esv_password = new EmptyStringValidator(ui->password,"Enter Password");
    registerValidator(esv_password);
    EmptyStringValidator * esv_name = new EmptyStringValidator(ui->name,"Enter Name");
    registerValidator(esv_name);
    SameStringValidator * ssv_password = new SameStringValidator(ui->password,ui->retypePassword,"Passwords doesen't match");
    registerValidator(ssv_password);

}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::bindOtherToUi()
{
   ui->retypePassword->setText(this->entity()->password());

   Service<Role> srv;
   QList<QSharedPointer<Role> > roles = this->entity()->listRoles();
   ui->tableWidget->setRowCount(srv.all().count());
   ui->tableWidget->setColumnCount(1);
   int i = 0;
   foreach(QSharedPointer<Role> r,srv.all())
   {
       auto it = std::find_if(ALL(roles),[r](QSharedPointer<Role> role){return r->id() == role->id();});
       QTableWidgetItem * ti;
       ti = new QTableWidgetItem;
       ti->setText(r->name());
       ti->setCheckState(it == roles.end() ? Qt::Unchecked : Qt::Checked);
       ti->setData(Qt::UserRole,r->id());
       ui->tableWidget->setItem(i,0,ti);
       i++;
   }
   m_passChanged = false;
}

bool UserForm::bindOtherToData()
{
    Service<Role> srv;
    this->entity()->clearRoles();
    for(int i = 0;i < ui->tableWidget->rowCount() ;i++){
        if(ui->tableWidget->item(i,0)->checkState()== Qt::Checked)
        {
            this->entity()->addRole(srv.loadById(ui->tableWidget->item(i,0)->data(Qt::UserRole).toInt()));
        }
    }
    PermissionService permService;
    if (m_passChanged){
        this->entity()->setPassword(permService.encryptPassword(ui->password->text()));
    }
    return true;
}


void UserForm::on_password_textChanged(const QString &)
{
    m_passChanged = true;
}

void UserForm::on_retypePassword_textChanged(const QString &)
{
    m_passChanged = true;
}
