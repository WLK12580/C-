#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QGroupBox>
#include<QRadioButton>
#include<QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

private:
    void timerFunc(QWidget *w);
    void precisFunc(QWidget *w); //
    void currentDispaly(QWidget *w);

private:
    void startLcdTimer();

private slots:
    void lcdSlot();
private:
    QTimer *m_timer=nullptr;
    QElapsedTimer *m_elapsedTimer=nullptr;
    QRadioButton *singlebtn=nullptr;
    QRadioButton *continuebtn=nullptr;
    QLCDNumber *hour=nullptr;
    QLCDNumber *min=nullptr;
    QLCDNumber *sec=nullptr;
};
#endif // WIDGET_H
