#include "insertdialog.h"
#include "ui_insertdialog.h"

insertDialog::insertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertDialog)
{
    ui->setupUi(this);
    ui->yearEdit->setValidator(new QIntValidator(this));
    ui->pagesEdit->setValidator(new QIntValidator(this));
    //ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

insertDialog::~insertDialog()
{
    delete ui;
}

QString insertDialog::getname() const
{
    return ui->nameEdit->text();
}

QString insertDialog::getauthor() const
{
    return ui->authorEdit->text();
}

QString insertDialog::getyear() const
{
    return ui->yearEdit->text();
}

QString insertDialog::getpublisher() const
{
    return ui->publisherEdit->text();
}

QString insertDialog::getloc() const
{
    return ui->locEdit->text();
}

QString insertDialog::getpages() const
{
    return ui->pagesEdit->text();
}

void insertDialog::checkText()
{
    QPushButton *ok = ui->buttonBox->button(QDialogButtonBox::Ok);
    QString year=ui->yearEdit->text(), pages=ui->yearEdit->text();
    int x=0,y=0;
    if (ui->nameEdit->text().isEmpty() || ui->authorEdit->text().isEmpty() || ui->yearEdit->text().isEmpty() || ui->publisherEdit->text().isEmpty() || ui->locEdit->text().isEmpty()
            || ui->pagesEdit->text().isEmpty() || ui->yearEdit->validator()->validate(year,x)==QValidator::State::Invalid || ui->pagesEdit->validator()->validate(pages,y)==QValidator::State::Invalid)
        ok->setEnabled(false);
    else
        ok->setEnabled(true);
}
