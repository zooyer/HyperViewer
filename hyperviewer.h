#ifndef HYPERVIEWER_H
#define HYPERVIEWER_H

#include <QWidget>
#include "windowwidget.h"
#include <QLabel>
#include <menubar.h>

class HyperViewer : public QWidget
{
    Q_OBJECT
public:
    explicit HyperViewer(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);

    void setStatus(QString info, bool success = false);

private:
    void initWidgets();
    void initLayout();
    void initTopBar();
    void initLicenseBar();
    void initMainWidget();
    void initMenuBar();
    void initMenuWidget();
    void initWindowWidget();
    void initBottomBar();

signals:

public slots:

private:
    QWidget *m_topBar;
    QWidget *m_licenseBar;
    QWidget *m_mainWidget;
    MenuBar *m_menuBar;
    QWidget *m_menuWidget;
    WindowWidget *m_windowWidget;
    QWidget *m_bottomBar;

    QLabel *m_status;
};

#endif // HYPERVIEWER_H
