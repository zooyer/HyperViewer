#include "button.h"
#include <QDebug>

Button::Button(QPushButton *button)
{
    this->m_QPushButton = button;
}

QPushButton &Button::getQPushButton()
{
    return *this->m_QPushButton;
}

void Button::setBackground(QColor font, QColor normal, QColor hover, QColor pressed, QColor checked, QColor disable)
{
    this->m_QPushButton->setFixedSize(this->m_QPushButton->size());


    QString qss = QString("QPushButton{color:rgb(%1,%2,%3);}");
    qss = qss.arg(font.red()).arg(font.green()).arg(font.blue());
    qss.append("QPushButton{background-color:rgba(%1,%2,%3,%4)}");
    qss = qss.arg(normal.red()).arg(normal.green()).arg(normal.blue()).arg(normal.alpha());
    qss.append("QPushButton::hover{background-color:rgba(%1,%2,%3,%4)}");
    qss = qss.arg(hover.red()).arg(hover.green()).arg(hover.blue()).arg(hover.alpha());
    qss.append("QPushButton::pressed{background-color:rgba(%1,%2,%3,%4)}");
    qss = qss.arg(pressed.red()).arg(pressed.green()).arg(pressed.blue()).arg(pressed.alpha());
    qss.append("QPushButton::checked{background-color:rgba(%1,%2,%3,%4)}");
    qss = qss.arg(checked.red()).arg(checked.green()).arg(checked.blue()).arg(checked.alpha());
    qss.append("QPushButton::disable{background-color:rgba(%1,%2,%3,%4)}");
    qss = qss.arg(disable.red()).arg(disable.green()).arg(disable.blue()).arg(disable.alpha());

    appendStyleSheet(qss);
}

void Button::setButtonStyle(QString imgsrc, QSize size, int line)
{

    int btn_w = size.width();
    int btn_h = size.height();

    this->m_QPushButton->setFixedSize(size);

    QString css = "QPushButton{border-width: 41px; border-image: url(%1)  %6 0 0 %2 repeat  repeat;border-width: 0px; border-radius: 0px;}";
    css.append("QPushButton::hover{border-image: url(%1) %6 0 0 %3  repeat  repeat;}");
    css.append("QPushButton::pressed{border-image: url(%1) %6  0 0 %4 repeat  repeat;}");
    css.append("QPushButton::checked{border-image: url(%1) %6  0 0 %4 repeat  repeat;}");
    css.append("QPushButton::disabled{border-image: url(%1) %6  0 0 %5 repeat  repeat;}");
    css = css.arg(imgsrc).arg(0).arg(btn_w * 1).arg(btn_w * 2).arg(btn_w * 3).arg(line * btn_h);

    appendStyleSheet(css);
}

void Button::setFontColor(QColor c)
{
    //color: rgb(255, 255, 255);
    QString qss = "QPushButton{color:rgb(%1,%2,%3)}";
    qss = qss.arg(c.red()).arg(c.green()).arg(c.blue());//.arg(c.alpha());

    appendStyleSheet(qss);
}

void Button::setRadius(int radius)
{
    QString qss = QString("QPushButton{border-radius:%1px;}").arg(radius);
    appendStyleSheet(qss);

}

void Button::appendStyleSheet(QString qss)
{
    if (this->m_QPushButton->styleSheet() != "") {
        qss = this->m_QPushButton->styleSheet() + ";" + qss;
    }
    qDebug() << "------------" << qss;

    this->m_QPushButton->setStyleSheet(qss);
}
