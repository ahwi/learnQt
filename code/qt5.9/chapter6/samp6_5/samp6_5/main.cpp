#include "qwmainwindow.h"
#include "qdlglogin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgLogin d;
    if(d.exec() == QDialog::Accepted){
        QWMainWindow w;
        w.show();
        return a.exec();
    }
    else
        return 0;
}
