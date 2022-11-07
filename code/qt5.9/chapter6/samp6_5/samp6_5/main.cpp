#include "qwmainwindow.h"
#include "qdlglogin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QWMainWindow w;
//    w.show();
    QDlgLogin d;
    d.exec();
    return a.exec();
}
