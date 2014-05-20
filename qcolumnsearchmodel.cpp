#include "qcolumnsearchmodel.h"

#include <QDebug>

QColumnSearchModel::QColumnSearchModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void QColumnSearchModel::enableColumn(int column, bool enable)
{
    beginResetModel();
    mapEnabled[column] = enable;
    endResetModel();
}

void QColumnSearchModel::reset()
{
    beginResetModel();
    mapEnabled.clear();
    endResetModel();
}

bool QColumnSearchModel::filterAcceptsRow(int source_row, const QModelIndex &) const
{
    QRegExp rex = filterRegExp();
    if(rex.isEmpty()) return true;

    QAbstractItemModel *source = sourceModel();
    qDebug() << "Looking at row" << source_row << "with regex" << rex;
    for(int i = 0; i < source->columnCount(); ++i) {
        bool columnEnabled = (!mapEnabled.contains(i) || mapEnabled[i]);
        if(columnEnabled)
        {
            qDebug() << "Column" << i << "enabled.";
            QString content = source->data(source->index(source_row, i)).toString();
            int index = rex.indexIn(content);
            qDebug() << "Column" << i << "content:" << content << "index:" << index;
            if(rex.indexIn(content) >= 0) {
                return true;
            }
        }
    }
    return false;
}
