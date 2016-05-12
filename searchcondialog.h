#ifndef SEARCHCONDIALOG_H
#define SEARCHCONDIALOG_H

#include <QDialog>
#include "qsearchtablemodel.h"

namespace Ui {
class SearchConDialog;
}

class SearchConDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchConDialog(QWidget *parent = 0);
    ~SearchConDialog();

    QString getSQL();

public slots:
    void clears();
    void deleteSelect();
    void addCondition();
    void addAll();
    void addOne();

private slots:
    void on_concomboBox_currentIndexChanged(int index);

private:
    Ui::SearchConDialog *ui;
    QSearchTableModel *model;
};

#endif // SEARCHCONDIALOG_H
