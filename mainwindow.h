#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "qdsvtablemodel/qdsvtablemodel.h"
#include "qcolumnsearchmodel.h"

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);
    void on_actionImport_CSV_triggered();
    void on_pushButton_clicked();
    void on_checkAll_toggled(bool checked);
    void on_listWidget_itemChanged(QListWidgetItem *item);

private:
    void loadFile(const QString &filename);

    Ui::MainWindow *ui;
    QColumnSearchModel *wrap;
    QDsvTableModel *model;
};

#endif // MAINWINDOW_H
