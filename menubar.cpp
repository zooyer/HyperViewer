#include "menubar.h"

#define PROFILE_BUTTON_HEIGHT 70
#define MENU_BUTTON_HEIGHT 48

MenuBar::MenuBar(QWidget *parent) : QWidget(parent)
{
    initMenuButton();
    initConnect();

}

void MenuBar::setUserName(QString name)
{
    m_profile->setText(name);
}

void MenuBar::setOnline()
{

}

void MenuBar::setOffline()
{

}

void MenuBar::setUnlogin()
{

}

void MenuBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void MenuBar::initMenuButton()
{
    QPushButton *profile = new QPushButton(this);
    QPushButton *control = new QPushButton(this);
    QPushButton *management = new QPushButton(this);
    QPushButton *meeting = new QPushButton(this);
    QPushButton *computers = new QPushButton(this);
    QPushButton *chat = new QPushButton(this);
    QPushButton *logo = new QPushButton(this);

    profile->setFixedHeight(PROFILE_BUTTON_HEIGHT);
    control->setFixedHeight(MENU_BUTTON_HEIGHT);
    management->setFixedHeight(MENU_BUTTON_HEIGHT);
    meeting->setFixedHeight(MENU_BUTTON_HEIGHT);
    computers->setFixedHeight(MENU_BUTTON_HEIGHT);
    chat->setFixedHeight(MENU_BUTTON_HEIGHT);
    logo->setFixedHeight(QImage(":/image/logo_title.png").height());


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(profile);
    layout->addWidget(control);
    layout->addWidget(management);
    layout->addWidget(meeting);
    layout->addWidget(computers);
    layout->addWidget(chat);
    layout->addStretch();
    layout->addWidget(logo);

    profile->setFont(QFont("Microsoft YaHei"));
    control->setFont(QFont("Microsoft YaHei"));
    management->setFont(QFont("Microsoft YaHei"));
    meeting->setFont(QFont("Microsoft YaHei"));
    computers->setFont(QFont("Microsoft YaHei"));
    chat->setFont(QFont("Microsoft YaHei"));

    profile->setStyleSheet(getButtonStyleString(75).arg(":/image/profile_unlogin.png").arg(":/image/profile_unlogin.png"));
    control->setStyleSheet(getButtonStyleString(75).arg(":/image/control1.png").arg(":/image/control2.png"));
    management->setStyleSheet(getButtonStyleString(75).arg(":/image/management1.png").arg(":/image/management2.png"));
    meeting->setStyleSheet(getButtonStyleString(75).arg(":/image/meeting1.png").arg(":/image/meeting2.png"));
    computers->setStyleSheet(getButtonStyleString(75).arg(":/image/computers1.png").arg(":/image/computers2.png"));
    chat->setStyleSheet(getButtonStyleString(75).arg(":/image/chat1.png").arg(":/image/chat2.png"));
    logo->setStyleSheet(getButtonStyleString(0).arg(":/image/logo_title.png").arg(":/image/logo_title.png"));

    profile->setText("Profile");
    control->setText("Remote Control");
    management->setText("Remote Management");
    meeting->setText("Meeting");
    computers->setText("Computers && Contacts");
    chat->setText("Chat");

    m_profile = profile;
    m_control = control;
    m_management = management;
    m_meeting = meeting;
    m_computers = computers;
    m_chat = chat;
}

void MenuBar::initConnect()
{
    connect(m_profile, &QPushButton::clicked, [=](){
        enableAll();
        emit profileSignal();
        m_profile->setEnabled(false);
    });

    connect(m_control, &QPushButton::clicked, [=](){
        enableAll();
        emit controlSignal();
        m_control->setEnabled(false);
    });

    connect(m_management, &QPushButton::clicked, [=](){
        enableAll();
        emit managementSignal();
        m_management->setEnabled(false);
    });

    connect(m_meeting, &QPushButton::clicked, [=](){
        enableAll();
        emit meetingSignal();
        m_meeting->setEnabled(false);
    });

    connect(m_computers, &QPushButton::clicked, [=](){
        enableAll();
        emit computersSignal();
        m_computers->setEnabled(false);
    });

    connect(m_chat, &QPushButton::clicked, [=](){
        enableAll();
        emit chatSignal();
        m_chat->setEnabled(false);
    });
}

void MenuBar::enableAll()
{
    m_profile->setEnabled(true);
    m_control->setEnabled(true);
    m_management->setEnabled(true);
    m_meeting->setEnabled(true);
    m_computers->setEnabled(true);
    m_chat->setEnabled(true);
}

QString MenuBar::getButtonStyleString(int paddingLeft)
{
    QString css = "QPushButton{border:0px; color:rgb(75,76,78); text-align:left; padding-left:%1px; background-repeat:no-repeat; background-image:url(%2)1-20px}";
    css.append("QPushButton::hover{background-color:rgba(255,255,255,200);}");
    css.append("QPushButton::pressed{background-color:rgba(255,255,255,255);}");
    //css.append("QPushButton::checked{background-color:rgba(0,0,0,0);}");
    css.append("QPushButton::disabled{background-image:url(%3); background-color:rgba(255,255,255,255);font-weight:bold;color:rgb(3,143,244)};}");

    return css.arg(paddingLeft);
}
