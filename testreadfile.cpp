#include "testreadfile.h"
#include <QDebug>
#include <QImage>

TestReadFile::TestReadFile(QThread *parent) : QThread(parent)
{

}

void TestReadFile::run()
{
    qDebug() << "in thread!";
    for (int i=0; i<3888; i++)
    {
        QString file = QString().sprintf("F:\\Project\\Go\\src\\hole\\download\\output\\jpg\\%05d.jpg", i);
        qDebug() << "file:" << file;
        QImage img(file);
        qDebug() << "size:" << img.width();
        emit sendImage(img);
        usleep(20000);
    }

    qDebug() << "out thread!";
}
