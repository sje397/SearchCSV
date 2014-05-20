#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QListWidgetItem>
#include <QDebug>

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
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open CSV"), "", tr("CSV Files (*.csv)"));
    model->loadFromFile(fileName);
    ui->tableView->resizeColumnsToContents();

    ui->listWidget->clear();
    wrap->reset();
    for(int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        QListWidgetItem *item = new QListWidgetItem(QString("Column %1").arg(i), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Checked); // AND initialize check state
        item->setData(Qt::UserRole, QVariant(i));
    }
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(itemChanged(QListWidgetItem*)));
}

void MainWindow::on_pushButton_clicked()
{
    wrap->setFilterRegExp("");
}

void MainWindow::itemChanged(QListWidgetItem *item)
{
    wrap->enableColumn(item->data(Qt::UserRole).toInt(), item->checkState() == Qt::Checked);
    //wrap->setFilterRegExp(ui->lineEdit->text());
}
