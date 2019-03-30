#include "windowwidget.h"

WindowWidget::WindowWidget(QWidget *parent) : QWidget(parent)
{
    QStackedWidget *stack = new QStackedWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(stack);

    m_login = new QWidget(stack);
    m_profile = new QWidget(stack);
    m_control = new QWidget(stack);
    m_management = new QWidget(stack);
    m_meeting = new QWidget(stack);
    m_computers = new QWidget(stack);
    m_chat = new QWidget(stack);

    m_login->setStyleSheet("background:rgb(250,250,250)");
    m_profile->setStyleSheet("background:yellow");
    m_control->setStyleSheet("background:red");
    m_management->setStyleSheet("background:green");
    m_meeting->setStyleSheet("background:pink");
    m_computers->setStyleSheet("background:orange");
    m_chat->setStyleSheet("background:blue");

    stack->addWidget(m_login);
    stack->addWidget(m_profile);
    stack->addWidget(m_control);
    stack->addWidget(m_management);
    stack->addWidget(m_meeting);
    stack->addWidget(m_computers);
    stack->addWidget(m_chat);

    stack->setStyleSheet("background:#123481");

    m_stack = stack;
}

void WindowWidget::switchLogin()
{
    m_stack->setCurrentIndex(0);
}

void WindowWidget::switchProfile()
{
    m_stack->setCurrentIndex(1);
}

void WindowWidget::switchControl()
{
    m_stack->setCurrentIndex(2);
}

void WindowWidget::switchManagement()
{
    m_stack->setCurrentIndex(3);
}

void WindowWidget::switchMeeting()
{
    m_stack->setCurrentIndex(4);
}

void WindowWidget::switchComputers()
{
    m_stack->setCurrentIndex(5);
}

void WindowWidget::switchChat()
{
    m_stack->setCurrentIndex(6);
}
