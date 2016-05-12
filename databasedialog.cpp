#include "databasedialog.h"
#include "ui_databasedialog.h"

databaseDialog::databaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseDialog)
{
    ui->setupUi(this);
    ui->portEdit->setValidator(new QIntValidator(this));
}

databaseDialog::~databaseDialog()
{
    delete ui;
}

QString databaseDialog::getIP()
{
    return ui->addressEdit->text();
}

QString databaseDialog::getPort()
{
    return ui->portEdit->text();
}

QString databaseDialog::getUser()
{
    return ui->userEdit->text();
}

QString databaseDialog::getPwd()
{
    return ui->pwdEdit->text();
}

QString databaseDialog::getDatabase()
{
    return ui->databaseEdit->text();
}

QString databaseDialog::getTable()
{
    return ui->tableEdit->text();
}
