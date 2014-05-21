#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QListWidgetItem>
#include <QSettings>
#include <QDebug>

namespace {
const QString LAST_FILENAME("LastFilename");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QDsvTableModel(this);

    wrap = new QColumnSearchModel(this);
    wrap->setFilterKeyColumn(-1); // all cols
    wrap->setSourceModel(model);
    ui->tableView->setModel(wrap);

    QSettings settings;
    if(settings.contains(LAST_FILENAME)) {
        loadFile(settings.value(LAST_FILENAME).toString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    wrap->setFilterRegExp(arg1);
}

void MainWindow::on_actionImport_CSV_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open CSV"), "", tr("CSV Files (*.csv)"));
    if(!filename.isEmpty()) {
        loadFile(filename);
        QSettings().setValue(LAST_FILENAME, filename);
    }
}

void MainWindow::loadFile(const QString &filename)
{
    model->loadFromFile(filename);
    ui->tableView->resizeColumnsToContents();

    wrap->reset();

    ui->listWidget->clear();

    QSettings settings;
    for(int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        // column names stored in settings under keys of the form "<filename>.Col<i>"
        const QString key = QString("%1.Col%2").arg(filename).arg(i);
        const QString label( settings.value(key, QString("Column %1").arg(i + 1) ).toString() );
        wrap->setHeaderData(i, Qt::Horizontal, label);
        QListWidgetItem *item = new QListWidgetItem(label);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        item->setCheckState(Qt::Checked);
        item->setData(Qt::UserRole, i);
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_pushButton_clicked()
{
    wrap->setFilterRegExp("");
}

void MainWindow::on_checkAll_toggled(bool checked)
{
    wrap->enableAllColumns(checked);
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *it = ui->listWidget->item(i);
        it->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }
}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    const int col = item->data(Qt::UserRole).toInt();
    wrap->enableColumn(col, item->checkState() == Qt::Checked);

    QSettings settings;
    if(settings.contains(LAST_FILENAME)) {
        const QString filename = settings.value(LAST_FILENAME).toString();
        const QString key = QString("%1.Col%2").arg(filename).arg(col);
        QSettings().setValue(key, item->text());
        wrap->setHeaderData(col, Qt::Horizontal, item->text());
    }
}
