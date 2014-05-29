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
signals:

public slots:

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &) const;
private:
    QMap< int, bool > mapEnabled;
};

#endif // QCOLUMNSEARCHMODEL_H
