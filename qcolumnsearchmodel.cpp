#include "qcolumnsearchmodel.h"

#include <QDebug>

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
    enableAllColumns(true);
    endResetModel();
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
