#include "hyperviewer.h"

#include <QLayout>
#include <QLabel>
#define MENU_BAR_WIDTH 72

HyperViewer::HyperViewer(QWidget *parent) : QWidget(parent)
{
    // init window properties
    this->setWindowTitle("HyperViewer");
    this->setWindowIcon(QIcon(":/image/logo.png"));

    // init widgets
    initWidgets();

    // init layout
    initLayout();


    // init child widgets
    initTopBar();
    initLicenseBar();
    initMainWidget();
    initMenuBar();
    initMenuWidget();
    initWindowWidget();
    initBottomBar();

}

void HyperViewer::resizeEvent(QResizeEvent *event)
{
    if (this->width() >= 900) {
        this->m_menuBar->setFixedWidth(255);
    } else {
        this->m_menuBar->setFixedWidth(MENU_BAR_WIDTH);
    }

    QWidget::resizeEvent(event);
}

void HyperViewer::setStatus(QString info, bool success)
{
    m_status->setText(info);
    if (success)
        m_status->setStyleSheet("QLabel{background-image:url(:/image/status_success.png); padding-left:48px; background-repeat:no-repeat;}");
    else
        m_status->setStyleSheet("QLabel{background-image:url(:/image/status_failed.png); padding-left:48px; background-repeat:no-repeat;}");
}

void HyperViewer::initWidgets()
{

    QWidget *topBar = new QWidget(this);
    QWidget *licenseBar = new QWidget(this);
    QWidget *mainWidget = new QWidget(this);
    MenuBar *menuBar = new MenuBar(mainWidget);
    QWidget *menuWidget = new QWidget(mainWidget);
    WindowWidget *windowWidget = new WindowWidget(menuWidget);
    QWidget *bottomBar = new QWidget(menuWidget);

    this->m_topBar = topBar;
    this->m_licenseBar = licenseBar;
    this->m_mainWidget = mainWidget;
    this->m_menuBar = menuBar;
    this->m_menuWidget = menuWidget;
    this->m_windowWidget = windowWidget;
    this->m_bottomBar = bottomBar;
}

void HyperViewer::initLayout()
{
    this->setMinimumSize(700, 450);
    m_topBar->setFixedHeight(41);
    m_topBar->setStyleSheet("QWidget{background-color:rgb(0,100,200)}");
    m_licenseBar->setFixedHeight(24);
    m_licenseBar->setStyleSheet("QWidget{background-color:rgb(48,149,183)}");
    m_mainWidget->setStyleSheet("QWidget{background-color:rgb(233,237,242)}");

    QVBoxLayout *vHyperViewerLayout = new QVBoxLayout(this);
    vHyperViewerLayout->setMargin(0);
    vHyperViewerLayout->setSpacing(0);
    vHyperViewerLayout->addWidget(m_topBar);
    vHyperViewerLayout->addWidget(m_licenseBar);
    vHyperViewerLayout->addWidget(m_mainWidget);

    m_menuBar->setStyleSheet("MenuBar{background-color:rgb(233,237,242)}");
    m_menuBar->setFixedWidth(MENU_BAR_WIDTH);
    QWidget *line = new QWidget(m_mainWidget);
    line->setFixedWidth(1);
    line->setStyleSheet("QWidget{background-color:rgb(228,228,228)}");
    m_menuWidget->setStyleSheet("QWidget{background-color:rgb(250,250,250)}");

    QHBoxLayout *vMainWidgetLayout = new QHBoxLayout(m_mainWidget);
    vMainWidgetLayout->setMargin(0);
    vMainWidgetLayout->setSpacing(0);
    vMainWidgetLayout->addWidget(m_menuBar);
    vMainWidgetLayout->addWidget(line);
    vMainWidgetLayout->addWidget(m_menuWidget);

    m_windowWidget->setStyleSheet("QWidget{background-color:rgb(250,250,250)}");
    m_bottomBar->setFixedHeight(46);
    m_bottomBar->setStyleSheet("QWidget{background-color:rgb(250,250,250)}");
    line = new QWidget(m_menuWidget);
    line->setFixedHeight(1);
    line->setStyleSheet("QWidget{background-color:rgb(228,228,228)}");

    QVBoxLayout *vMenuWidgetLayout = new QVBoxLayout(m_menuWidget);
    vMenuWidgetLayout->setMargin(0);
    vMenuWidgetLayout->setSpacing(0);
    vMenuWidgetLayout->addWidget(m_windowWidget);
    vMenuWidgetLayout->addWidget(line);
    vMenuWidgetLayout->addWidget(m_bottomBar);
}

void HyperViewer::initTopBar()
{

}

void HyperViewer::initLicenseBar()
{
    QLabel *label = new QLabel(m_licenseBar);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setStyleSheet("QLabel{color:#ffffFf}");
    label->setFont(QFont("Microsoft YaHei"));
    label->setText("Free license (non-commercial use only)");
    QHBoxLayout *layout = new QHBoxLayout(m_licenseBar);
    layout->setMargin(0);
    layout->addWidget(label);
}

void HyperViewer::initMainWidget()
{

}

void HyperViewer::initMenuBar()
{

}

void HyperViewer::initMenuWidget()
{

}

void HyperViewer::initWindowWidget()
{
    connect(m_menuBar, &MenuBar::profileSignal, [=](){
        m_windowWidget->switchProfile();
        // todo switch login
    });

    connect(m_menuBar, &MenuBar::controlSignal, [=](){
        m_windowWidget->switchControl();
    });

    connect(m_menuBar, &MenuBar::managementSignal, [=](){
        m_windowWidget->switchManagement();
    });

    connect(m_menuBar, &MenuBar::meetingSignal, [=](){
        m_windowWidget->switchMeeting();
    });

    connect(m_menuBar, &MenuBar::computersSignal, [=](){
        m_windowWidget->switchComputers();
    });

    connect(m_menuBar, &MenuBar::chatSignal, [=](){
        m_windowWidget->switchChat();
    });
}

void HyperViewer::initBottomBar()
{
    m_status = new QLabel(m_bottomBar);
    setStatus("Ready to connect");
    m_status->setFont(QFont("Microsoft YaHei"));
    QHBoxLayout *layout = new QHBoxLayout(m_bottomBar);
    layout->setMargin(0);
    layout->addWidget(m_status);
}
