#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QColor>
#include <QPainter>
#include <QDesktopWidget>
#include <QLabel>
#include <QRgb>
#include <QTimer>
#include <QDebug>
#include "button.h"

QLabel *label;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    //qDebug() << (QString("2BC0").toUInt(nullptr, 16));
    ui->setupUi(this);



    ui->pushButton_2->setFont(QFont("Microsoft YaHei"));
    Button(ui->pushButton_2).setRadius(15);
    Button(ui->pushButton_2).setBackground(QColor("yellow"), QColor(0,0,0,0), QColor(0, 0, 0, 80), QColor(0, 0, 0, 80), QColor(""), QColor(""));
    //ui->pushButton_2->setStyleSheet(QString("QPushButton{color:rgb(255,255,255)}"));
    //Button(ui->pushButton_2).setFontColor(QColor(255, 255, 255, 255));

    //Button(ui->pushButton_2).setButtonStyle(":/image/btn 45x29.png", QSize(40, 40), 1);
    //ui->pushButton_2->setStyleSheet(";background-color:rgba(255,255,255,100)");
    //ui->pushButton_2->setStyleSheet(ui->pushButton_2->styleSheet() + ";color:#fff");

    return;
    ui->widget->hide();
    ui->widget_4->hide();
    ui->tabWidget->hide();
    label = new QLabel(this);
    setAttribute(Qt::WA_OpaquePaintEvent);

    QTimer *timer = new QTimer(this);
    //timer.setInterval(1000);
    connect(timer, &QTimer::timeout, [=](){
        // timer.stop();
        this->update();
        qDebug() << "updating...";
    });
    timer->start(0);
}

void MainWindow::flush()
{
    static QImage image, mini;
    static QImage lastImage;
    QPainter painter(this);
    painter.setPen(QColor(245, 40, 111));

    QScreen *screen = QApplication::primaryScreen(); //获取当前程序的主窗口对象
    QPixmap map = screen->grabWindow(QApplication::desktop()->winId()); //调用主窗口对象的捕捉窗口图像，并传递桌面窗口的id号
    image = map.toImage();
    int w = image.width() / 10;
    int h = image.height() / 10;

    if (lastImage.width() > 0)
    {
        for (int i=0; i<10; i++)
        {
            for (int j=0; j<10; j++)
            {
                mini = image.copy(j * w, i * h, w, h);
                int num = this->compare(lastImage.copy(j * w, i * h, w, h), mini, 10);
                if (num < 95)
                {
                    qDebug() << "image" << j << i << num;
                    QPainter p(&image);
                    p.setPen(QColor(245, 40, 111));
                    p.drawImage(j * w, i * h, mini);
                    //painter.drawPixmap(j * w, i * h, QPixmap::fromImage(mini));
                    //p.drawPixmap(j * w, i * h, QPixmap::fromImage(mini));
                    p.drawRect(j * w, i * h, w, h);
                }
            }
        }
    } else
    {
        qDebug() << "first paint.";
        label->setGeometry(0, 0, image.width(), image.height());
        painter.drawPixmap(0, 0, QPixmap::fromImage(image));
        //label->setPixmap(QPixmap::fromImage(image));
    }
    painter.drawPixmap(0, 0, QPixmap::fromImage(image));
//    for (int y=0; y<image.height(); y++)
//    {
//        for (int x=0; x<image.width(); x++)
//        {
//            QColor color = image.pixel(x, y);
//            int aver = (color.red() + color.green() + color.blue()) / 3;
//            image.setPixel(x, y, qRgb(aver, aver, aver));
//        }
//    }

    lastImage = image;
    //update();
}


int MainWindow::compare(const QImage &i1, const QImage &i2, int tolerance)
{
    int similpoint = 0;
    int w = i1.width() < i2.width() ? i1.width() : i2.width();
    int h = i1.height() < i2.height() ? i1.height() : i2.height();

    QColor c1, c2;

    for (int y=0; y<h; y++)
    {
        for (int x=0; x<w; x++)
        {
            c1 = i1.pixel(x, y);
            c2 = i2.pixel(x, y);

            if (qAbs(c1.red() - c2.red()) < tolerance &&
                qAbs(c1.green() - c2.green()) < tolerance &&
                qAbs(c1.blue() - c2.blue()) < tolerance &&
                qAbs(c1.alpha() - c2.alpha()) < tolerance &&
                qAbs(c1.red() + c1.green() + c1.blue() + c1.alpha() -
                     c2.red() - c2.green() - c2.blue() - c2.alpha()) < tolerance)
            {
                ++similpoint;
            }
        }
    }

    return (similpoint * 100) / (w * h);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    return;
    qDebug() << "paintEvent";
//    QScreen *screen = QApplication::primaryScreen(); //获取当前程序的主窗口对象
//    QPixmap map = screen->grabWindow(QApplication::desktop()->winId()); //调用主窗口对象的捕捉窗口图像，并传递桌面窗口的id号
//    //map.save("/kkk.jpg"); //保存图像
//    QImage image = map.toImage();

//    for (int y=0; y<image.height(); y++)
//    {
//        //QRgb * line = (QRgb *)image.scanLine(y);
//        for (int x=0; x<image.width(); x++)
//        {
//            QColor color = image.pixel(x, y);
//            int aver = (color.red() + color.green() + color.blue()) / 3;
//            //int aver = (qRed(line[x]) + qGreen(line[x]) + qRed(line[x])) / 3;
//            image.setPixel(x, y, qRgb(aver, aver, aver));
//        }
//    }

//    label->setGeometry(0, 0, image.width(), image.height());
//    //label->setPixmap(QPixmap::fromImage(image));

//    QPainter painter(this);
//    painter.drawPixmap(0, 0, QPixmap::fromImage(image));
    flush();

    QWidget::paintEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
