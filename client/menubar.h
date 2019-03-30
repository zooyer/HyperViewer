#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>

class MenuBar : public QWidget
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget *parent = nullptr);
    void setUserName(QString name);
    void setOnline();
    void setOffline();
    void setUnlogin();

    void paintEvent(QPaintEvent *event);
    void initMenuButton();
    void initConnect();
    void enableAll();

    QString getButtonStyleString(int paddingLeft);
signals:
    void profileSignal();
    void controlSignal();
    void managementSignal();
    void meetingSignal();
    void computersSignal();
    void chatSignal();
public slots:

private:
    QPushButton *m_profile;
    QPushButton *m_control;
    QPushButton *m_management;
    QPushButton *m_meeting;
    QPushButton *m_computers;
    QPushButton *m_chat;
    QPushButton *m_logo;
};

#endif // MENUBAR_H
