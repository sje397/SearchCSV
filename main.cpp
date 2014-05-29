#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("SearchCSV");
    a.setApplicationVersion("1.0");
    a.setOrganizationDomain("scottellis.com.au");
    a.setOrganizationName("Scott Ellis");

    MainWindow w;
    w.show();

    return a.exec();
}
