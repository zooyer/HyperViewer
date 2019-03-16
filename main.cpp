#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>
#include "hyperviewer.h"
#include "remoteviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HyperViewer m;
    m.show();
    RemoteViewer r(QSize(800, 600));
    r.show();

    return a.exec();
}
