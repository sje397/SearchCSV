#include "qcolumnsearchmodel.h"

QColumnSearchModel::QColumnSearchModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void QColumnSearchModel::enableColumn(int column, bool enable)
{
    if(enable != mapEnabled[column])
    {
        beginResetModel();
        mapEnabled[column] = enable;
        endResetModel();
    }
}

void QColumnSearchModel::enableAllColumns(bool enable)
{
    beginResetModel();
    const int cols = sourceModel()->columnCount();
    for(int i = 0; i < cols; ++i) {
        mapEnabled[i] = enable;
    }
    endResetModel();
}

void QColumnSearchModel::reset()
{
    beginResetModel();
    mapEnabled.clear();
    mapNames.clear();
    enableAllColumns(true);
    endResetModel();
}

QVariant QColumnSearchModel::headerData(int section, Qt::Orientation, int role) const
{
    if(role == Qt::DisplayRole) {
        if(mapNames.contains(section)) return mapNames[section];
        return QString("Column %1").arg(section + 1);
    }
    return QVariant();
}

bool QColumnSearchModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        mapNames[section] = value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

bool QColumnSearchModel::filterAcceptsRow(int source_row, const QModelIndex &) const
{
    QRegExp rex = filterRegExp();
    if(rex.isEmpty()) return true;

    QAbstractItemModel *source = sourceModel();
    const int cols = source->columnCount();
    for(int i = 0; i < cols; ++i) {
        bool columnEnabled = (!mapEnabled.contains(i) || mapEnabled[i]);
        if(columnEnabled)
        {
            QString content = source->data(source->index(source_row, i)).toString();
            if(rex.indexIn(content) >= 0) {
                return true;
            }
        }
    }
    return false;
}
