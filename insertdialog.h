#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class insertDialog;
}

class insertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit insertDialog(QWidget *parent = 0);
    ~insertDialog();
    QString getname() const;
    QString getauthor() const;
    QString getyear() const;
    QString getpublisher() const;
    QString getloc() const;
    QString getpages() const;

public slots:
    void checkText();

private:
    Ui::insertDialog *ui;
};

#endif // INSERTDIALOG_H
