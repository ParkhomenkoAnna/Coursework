#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); QApplication::setStyle("Cleanlooks");
    MainWindow w;
    w.show();

    return a.exec();
}
