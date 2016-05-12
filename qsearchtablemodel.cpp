#include "qsearchtablemodel.h"
#include <iostream>

QSearchTableModel::QSearchTableModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

int QSearchTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return fields.count();
}

int QSearchTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant QSearchTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        if (index.column() == 0)
        {
            switch (types[index.row()])
            {
                case OR:
                    return QString("或");
                case AND:
                    return QString("且");
            }

        }
        else if (index.column() == 2)
        {
            switch (conds[index.row()])
            {
            case EQU:
                return QString("等于");
            case NE:
                return QString("不等于");
            case GT:
                return QString("大于");
            case GE:
                return QString("大于等于");
            case LT:
                return QString("小于");
            case LE:
                return QString("小于等于");
            case LIKE:
                return QString("模糊匹配");
            case LIKES:
                return QString("模糊包含");
            case IN:
                return QString("包括");
            case LB:
                return QString("(");
            case RB:
                return QString(")");
            case NOT:
                return QString("NOT");
            case NIN:
                return QString("不包括");
            }
        }
        else if (conds[index.row()] == LB || conds[index.row()] == RB || conds[index.row()] == NOT)
            return QVariant();
        else if (index.column() == 1)
        {
            return fields[index.row()];
        }
        else if (index.column() == 3)
        {
            return vals[index.row()];
        }
        return QVariant();
    }
    return QVariant();
}

QVariant QSearchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return section+1;
    switch (section)
    {
    case 0:
        return QString("类型");
    case 1:
        return QString("域");
    case 2:
        return QString("条件");
    case 3:
        return QString("值");
    }
    return QVariant();
}

int QSearchTableModel::count()
{
    return types.count();
}

void QSearchTableModel::clear()
{
    int i= count();
    QModelIndex topleft = createIndex(0,0);
    QModelIndex bottomright = createIndex(i-1, 3);
    types.clear();
    fields.clear();
    conds.clear();
    vals.clear();
    emit dataChanged(topleft, bottomright);
}
void QSearchTableModel::remove(const int i)
{
    QModelIndex topleft = createIndex(i,0);
    QModelIndex bottomright = createIndex(i, 3);
    types.remove(i);
    fields.remove(i);
    conds.remove(i);
    vals.remove(i);
    emit dataChanged(topleft, bottomright);
}
void QSearchTableModel::add(CONTYPE isor, QString field, CONDITION cond, QString val)
{
    int i= count();
    types.push_back(isor);
    fields.push_back(field);
    conds.push_back(cond);
    vals.push_back(val);
    QModelIndex topleft = createIndex(0,0);
    QModelIndex bottomright = createIndex(i, 3);
    emit dataChanged(topleft, bottomright);
}

QString QSearchTableModel::getSQL()
{
    QString ret="";
    if (fields.isEmpty())
        return ret;
    if (types[0] == AND)
        ret += "TRUE";
    else
        ret == "FALSE";
    int c=count();
    for (int i=0; i<c; ++i)
    {
        if (i==0 || (conds[i-1]!=LB && conds[i-1]!=NOT && conds[i]!=RB ))
        switch (types[i])
        {
            case OR:
                ret += " OR ";
                break;
            case AND:
                ret += " AND ";
                break;
        }
        if (conds[i]!=LB && conds[i]!=RB && conds[i]!=NOT)
        {
            ret += '(';
            ret += "'";
            ret += vals[i];
            ret += "'";
        }
        switch (conds[i]) {
        case EQU:
            ret += " = ";
            break;
        case NE:
            ret += " <> ";
            break;
        case GT:
            ret += " < ";
            break;
        case GE:
            ret += " <= ";
            break;
        case LT:
            ret += " > ";
            break;
        case LE:
            ret += " >= ";
            break;
        case LIKE:
            ret += " ~~~ ";
            break;
        case LIKES:
            ret += " ~~~ ANY(";
            break;
        case IN:
            ret += "=ANY(";
            break;
        case LB:
            ret += '(';
            continue;
        case RB:
            ret +=')';
            continue;
        case NOT:
            ret += "NOT ";
            continue;
        case NIN:
            ret += "<>ALL(";
            break;
        default:
            break;
        }
        ret += fields[i];
        if (conds[i] == IN || conds[i] == NIN || conds[i] == LIKES)
            ret += ')';
        ret += ')';
    }
    qDebug(qUtf8Printable(ret));
    return ret;
}
