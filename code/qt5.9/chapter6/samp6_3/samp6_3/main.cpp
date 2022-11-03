#include "mainwindow.h"
#include "qformdoc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    QFormDoc w;
    w.show();
    return a.exec();
}
