#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QObject
{
    Q_OBJECT
private:
    QPushButton *m_QPushButton;
public:
    Button(QPushButton *button);
    QPushButton &getQPushButton();
    void setButtonStyle(QString imgsrc, QSize size, int line);
    void setFontColor(QColor c);
    void setRadius(int radius);
    void setBackground(QColor font, QColor normal, QColor hover, QColor pressed, QColor checked, QColor disable);
private:
    void appendStyleSheet(QString qss);

signals:

public slots:
};

#endif // BUTTON_H
