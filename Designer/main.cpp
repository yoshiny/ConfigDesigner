#include "SMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SMainWindow w;
    w.showMaximized();
    return a.exec();
}
