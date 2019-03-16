#include "remoteviewer.h"
#include "testreadfile.h"
#include <QPaintEvent>
#include <QDebug>

RemoteViewer::RemoteViewer(QSize size, QWidget *parent) :QWidget(parent)
{
    // 初始化默认大小为对方分辨率大小
    this->resize(size);
    this->setWindowTitle("RemoteViewer");
    this->setWindowIcon(QIcon(":/image/logo.png"));
    this->setStyleSheet("RemoteViewer{background:black}");

    TestReadFile *test = new TestReadFile();

    connect(test, &TestReadFile::sendImage, [=](QImage &img){
        updateImage(img);
    });

    test->start();
}

void RemoteViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (m_image.size().width() <= 0) return;


//    if (map.width() > width())
//    {
//        double_t h = map.height() * width() / map.width();
//        double_t w = width();
//        if (h > height())
//        {
//            w = w * height() / h;
//            h = height();
//        }
//        ui->win->resize(w, h);
//    }
//    else
//    {
//        ui->win->resize(map.size());
//    }

//    ui->win->move((width() - ui->win->width()) / 2, (height() - ui->win->height()) / 2);


    double_t w = m_image.width();
    double_t h = m_image.height();

    if (h > height())
    {
        w = w * height() / h;
        h = height();
    }

    if (w > width())
    {
        h = h * width() / w;
        w = width();
    }

    if (w != m_image.width() || h != m_image.height())
        m_image = m_image.scaled(w, h);


    painter.drawImage((width() - w) / 2, (height() - h) / 2, m_image);


    QWidget::paintEvent(event);
}

void RemoteViewer::mouseMoveEvent(QMouseEvent *event)
{

}

void RemoteViewer::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void RemoteViewer::mousePressEvent(QMouseEvent *event)
{

}

void RemoteViewer::mouseReleaseEvent(QMouseEvent *event)
{

}

void RemoteViewer::keyPressEvent(QKeyEvent *event)
{

}

void RemoteViewer::keyReleaseEvent(QKeyEvent *event)
{

}

void RemoteViewer::updateImage(QImage &img)
{
    m_image = img;
    update();
}
