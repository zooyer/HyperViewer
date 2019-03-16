#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>

class WindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = nullptr);
    void switchLogin();
    void switchProfile();
    void switchControl();
    void switchManagement();
    void switchMeeting();
    void switchComputers();
    void switchChat();

signals:

public slots:
private:
    QStackedWidget *m_stack;

    QWidget *m_login;
    QWidget *m_profile;
    QWidget *m_control;
    QWidget *m_management;
    QWidget *m_meeting;
    QWidget *m_computers;
    QWidget *m_chat;
};

#endif // WINDOWWIDGET_H
