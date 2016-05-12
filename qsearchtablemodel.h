#ifndef QSEARCHTABLEMODEL_H
#define QSEARCHTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>


class QSearchTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum CONDITION
    {
        LB=0,
        RB,
        NOT,
        EQU,
        NE,
        GT,
        GE,
        LT,
        LE,
        LIKE,
        LIKES,
        IN,
        NIN
    };

    enum CONTYPE
    {
        AND,
        OR
    };

    QSearchTableModel(QObject *parent = Q_NULLPTR);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    int count();
    void clear();
    void remove(const int i);
    void add(CONTYPE isor, QString field, CONDITION cond, QString val);
    QString getSQL();

private:
    QVector<CONTYPE>   types;
    QVector<QString> fields;
    QVector<CONDITION> conds;
    QVector<QString> vals;
};

#endif // QSEARCHTABLEMODEL_H
