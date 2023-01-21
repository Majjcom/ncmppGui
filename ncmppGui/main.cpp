#include "src/mainwindow.h"

#include <QStyleFactory>
#include <QApplication>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
