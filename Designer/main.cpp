#include "SMainWindow.h"

#include "SApplication.h"

int main(int argc, char *argv[])
{
    SApplication a(argc, argv);
    SMainWindow w;
    w.showMaximized();
    return a.exec();
}
