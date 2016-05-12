#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pqxx/pqxx>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db(QSqlDatabase::addDatabase("QPSQL")),
    model(nullptr),
    i_dialog(new insertDialog(this)),
    s_dialog(new SearchConDialog(this)),
    d_dialog(new databaseDialog(this)),
    database("ex4"),
    table("publish")
{
    ui->setupUi(this);
    db.setDatabaseName(database);
    if (!db.open())
        qWarning("Error openning Database");
    model = new QSqlTableModel(this, db);
    model->setTable(table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(6);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::list()
{
    model->select();
}

void MainWindow::commit()
{
    model->submitAll();
    if (model->lastError().isValid())
        qWarning(qUtf8Printable(model->lastError().text()));
    model->select();
}

void MainWindow::rollback()
{
    model->revertAll();
    model->select();
}

void MainWindow::deleteselect()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if (select->hasSelection())
    {
        for (auto &x : select->selectedIndexes())
            model->removeRow(x.row());
    }
}

void MainWindow::insertRow()
{
    if (i_dialog->exec() == QDialog::Accepted)
    {
        QSqlRecord record = model->record();
        record.setValue(0, QVariant(i_dialog->getname()));
        QString author=i_dialog->getauthor();
        author.replace(' ', "");//.replace(',', "\\', \\'");
        author = QString("{%1}").arg(author);
        record.setValue(1, QVariant(author));
        record.setValue(2, QVariant(i_dialog->getyear().toInt()));
        record.setValue(3, QVariant(i_dialog->getpublisher()));
        record.setValue(4, QVariant(i_dialog->getloc()));
        record.setValue(5, QVariant(i_dialog->getpages().toInt()));
        record.setGenerated(6, false);
        model->insertRecord(-1, record);
    }
}

void MainWindow::insertCond()
{
    if (s_dialog->exec() == QDialog::Accepted)
    {
        model->setFilter(s_dialog->getSQL());
        model->select();
    }
}

void MainWindow::connectDB()
{
    if (d_dialog->exec() == QDialog::Accepted)
    {
        ip = d_dialog->getIP();
        port = d_dialog->getPort();
        user = d_dialog->getUser();
        pwd = d_dialog->getPwd();
        database = d_dialog->getDatabase();
        table = d_dialog->getTable();
        db.close();
        if (!ip.isEmpty())
        {
            qDebug() << "ip:" << ip;
            db.setHostName(ip);
        }
        if (!port.isEmpty())
        {
            qDebug() << "port:" << port;
            db.setPort(port.toInt());
        }
        if (!user.isEmpty())
        {
            qDebug() << "user:" << user;
            db.setUserName(user);
        }
        if(!pwd.isEmpty())
        {
            qDebug() << "pwd:" << pwd;
            db.setPassword(pwd);
        }
        if (!database.isEmpty())
        {
            qDebug() << "database:" << database;
            db.setDatabaseName(database);
        }
        if (!db.open())
        {
            qWarning("Error openning Database");
            qWarning(qUtf8Printable(db.lastError().text()));
        }
        model->setTable(table);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        ui->tableView->hideColumn(6);
    }
}

void MainWindow::delAll()
{
    for (int i=0; i<model->rowCount(); ++i)
        model->removeRow(i);
}

void MainWindow::modAll()
{
    if (i_dialog->exec() == QDialog::Accepted)
    {
        if (!i_dialog->getname().isEmpty())
            for (int i=0; i<model->rowCount(); ++i)
                model->setData(model->index(i, 0), QVariant(i_dialog->getname()));
        if (!i_dialog->getauthor().isEmpty())
            for (int i=0; i<model->rowCount(); ++i)
                model->setData(model->index(i, 1), QVariant(i_dialog->getauthor()));
        if (!i_dialog->getyear().isEmpty())
            for (int i=0; i<model->rowCount(); ++i)
                model->setData(model->index(i, 2), QVariant(i_dialog->getyear()));
        if (!i_dialog->getpublisher().isEmpty())
            for (int i=0; i<model->rowCount(); ++i)
                model->setData(model->index(i, 3), QVariant(i_dialog->getpublisher()));
        if (!i_dialog->getloc().isEmpty())
            for (int i=0; i<model->rowCount(); ++i)
                model->setData(model->index(i, 4), QVariant(i_dialog->getloc()));
        if (!i_dialog->getpages().isEmpty())
            for (int i=0; i<model->rowCount(); ++i)
                model->setData(model->index(i, 5), QVariant(i_dialog->getpages()));
    }
}
