#include <QAbstractTableModel>
#include "searchcondialog.h"
#include "ui_searchcondialog.h"
#include "qsearchtablemodel.h"

SearchConDialog::SearchConDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchConDialog),
    model()
{
    ui->setupUi(this);
    model = new QSearchTableModel(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->show();
    QStringList f({"书名", "作者", "出版年", "出版社", "出版地", "页数"});
    QStringList d({"(", ")", "NOT", "等于", "不等于", "大于", "大于等于", "小于", "小于等于", "模糊匹配", "模糊包含","包含", "不包含"});
    ui->fieldcomboBox->addItems(f);
    for (int x=QSearchTableModel::LB; x<=QSearchTableModel::CONDITION::NIN; ++x)
    {
        ui->concomboBox->addItem(d[x], x);
    }
}

SearchConDialog::~SearchConDialog()
{
    delete ui;
}

void SearchConDialog::clears()
{
     model->clear();
     ui->tableView->setModel(nullptr);
     ui->tableView->setModel(model);
}

void SearchConDialog::deleteSelect()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if (select->hasSelection())
    {
        model->remove(select->selectedIndexes()[0].row());
        ui->tableView->setModel(nullptr);
        ui->tableView->setModel(model);
    }
}

void SearchConDialog::addCondition()
{
    model->add(ui->orcheckBox->isChecked()?QSearchTableModel::OR:QSearchTableModel::AND, ui->fieldcomboBox->currentText(), (QSearchTableModel::CONDITION)ui->concomboBox->currentData().toInt(), ui->valEdit->text());
    ui->tableView->setModel(nullptr);
    ui->tableView->setModel(model);
}

void SearchConDialog::addAll()
{
    ui->valEdit->setText(ui->valEdit->text() + "%");
}

void SearchConDialog::addOne()
{
    ui->valEdit->setText(ui->valEdit->text() + "_");
}

QString SearchConDialog::getSQL()
{
    return model->getSQL();
}

void SearchConDialog::on_concomboBox_currentIndexChanged(int index)
{
    QPushButton *one = ui->oneButton_2;
    QPushButton *all = ui->allButton;
    if (index == 9 || index == 10)
    {
        one->setEnabled(true);
        all->setEnabled(true);
    }
    else
    {
        one->setEnabled(false);
        all->setEnabled(false);
    }
}
