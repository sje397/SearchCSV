#ifndef QCOLUMNSEARCHMODEL_H
#define QCOLUMNSEARCHMODEL_H

#include <QSortFilterProxyModel>
#include <QMap>

class QColumnSearchModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QColumnSearchModel(QObject *parent = 0);
    void enableColumn(int column, bool enable);
    void enableAllColumns(bool enable);
    void reset();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setHeaderData(int section, Qt::Orientation orientation,
            const QVariant &value, int role = Qt::EditRole);
signals:

public slots:

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &) const;
private:
    QMap< int, bool > mapEnabled;
    QMap< int, QString > mapNames;
};

#endif // QCOLUMNSEARCHMODEL_H
