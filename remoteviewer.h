#ifndef REMOTEVIEWER_H
#define REMOTEVIEWER_H

#include <QWidget>
#include <QIcon>
#include <QImage>
#include <QPainter>

class RemoteViewer : public QWidget
{
    Q_OBJECT
public:
    explicit RemoteViewer(QSize size, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:

public slots:
    void updateImage(QImage &img);
private:
    QImage m_image;
};

#endif // REMOTEVIEWER_H
