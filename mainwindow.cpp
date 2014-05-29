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

    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(itemChanged(QListWidgetItem*)));

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
    QListWidgetItem *item = new QListWidgetItem("All", ui->listWidget);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    item->setData(Qt::UserRole, -1);

    for(int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        item = new QListWidgetItem(QString("Column %1").arg(i + 1), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        item->setData(Qt::UserRole, i);
    }
}

void MainWindow::on_pushButton_clicked()
{
    wrap->setFilterRegExp("");
}

void MainWindow::itemChanged(QListWidgetItem *item)
{
    int col = item->data(Qt::UserRole).toInt();
    if(col >= 0) {
        wrap->enableColumn(col, item->checkState() == Qt::Checked);
    } else {
        bool checked = item->checkState() == Qt::Checked;
        wrap->enableAllColumns(checked);
        for(int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem *it = ui->listWidget->item(i);
            it->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
        }
    }
}
