#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QtSql/QSqlError>

#include "insertdialog.h"
#include "searchcondialog.h"
#include "databasedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  void list();
  void rollback();
  void commit();
  void deleteselect();
  void insertRow();
  void insertCond();
  void connectDB();
  void delAll();
  void modAll();

private:
    Ui::MainWindow *ui;
    QSqlDatabase   db;
    QSqlTableModel *model;
    insertDialog *i_dialog;
    SearchConDialog *s_dialog;
    databaseDialog *d_dialog;
    QString ip;
    QString port;
    QString user;
    QString pwd;
    QString database;
    QString table;
};

#endif // MAINWINDOW_H
