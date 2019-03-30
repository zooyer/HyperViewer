#ifndef TESTREADFILE_H
#define TESTREADFILE_H

#include <QThread>

class TestReadFile : public QThread
{
    Q_OBJECT
public:
    explicit TestReadFile(QThread *parent = nullptr);
    void run();

signals:
    void sendImage(QImage &img);

public slots:
};

#endif // TESTREADFILE_H
