#include "src/mainwindow.h"

#include <QStyleFactory>
#include <QApplication>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    w->show();
    int ret = a.exec();
    delete w;
    return ret;
}
