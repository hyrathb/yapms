#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class databaseDialog;
}

class databaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit databaseDialog(QWidget *parent = 0);
    ~databaseDialog();
    QString getIP();
    QString getPort();
    QString getUser();
    QString getPwd();
    QString getDatabase();
    QString getTable();

private:
    Ui::databaseDialog *ui;
};

#endif // DATABASEDIALOG_H
