#include "widget.h"
#include "./ui_widget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QLCDNumber>
#include <QColor>
#include <QPalette>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    timerFunc(this);
    precisFunc(this);
    currentDispaly(this);
    startLcdTimer();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerFunc(QWidget *w){
    //groupbox
    QGroupBox *GBX=new QGroupBox(w);
    GBX->setGeometry(QRect(100,50,350,100));
    GBX->setTitle("Timer");
    //
//    QHBoxLayout *HLay=new QHBoxLayout(GBX);
//    HLay->setSpacing(10);
//    HLay->setContentsMargins(10,10,10,10);

    //
    QGridLayout *GLay=new QGridLayout(GBX);
    GLay->setHorizontalSpacing(10);
    GLay->setVerticalSpacing(10);
    GLay->setContentsMargins(10,10,10,10);

    QPushButton *startptb=new QPushButton(GBX);
    startptb->setText("Start");

    QPushButton *stoppbt=new QPushButton(GBX);
    stoppbt->setText("Stop");

    QPushButton *dynamicpbt=new QPushButton(GBX);
    dynamicpbt->setText("Dynamic");

    QLabel *label1=new QLabel(GBX);
    label1->setText("Timing Cycle");

    QSpinBox *spinbox=new QSpinBox(GBX);
    spinbox->setMaximum(2000);

    singlebtn=new QRadioButton(GBX);
    singlebtn->setText("Single Time");


    continuebtn=new QRadioButton(GBX);
    continuebtn->setText("Cuntinue Time");


    GLay->addWidget(startptb,0,0);
    GLay->addWidget(stoppbt,0,1);
    GLay->addWidget(dynamicpbt,0,2,1,2);//位于第一行，第三列，占据一行两列的位置
    GLay->addWidget(label1,1,0);
    GLay->addWidget(spinbox,1,1);
    GLay->addWidget(singlebtn,1,2);
    GLay->addWidget(continuebtn,1,3);

    GBX->setLayout(GLay);
}
void Widget::precisFunc(QWidget *w){
    //groupbox容器
    QGroupBox *GBX=new QGroupBox(w);
    GBX->setGeometry(QRect(100,170,350,60));
    GBX->setTitle("Precise Set");
    //    水平布局
    QHBoxLayout *HLay=new QHBoxLayout(GBX);
    HLay->setSpacing(10);
    HLay->setContentsMargins(10,10,10,10);

    QRadioButton *precise=new QRadioButton(GBX);
    precise->setText("Precise");

    QRadioButton *coarse=new QRadioButton(GBX);
    coarse->setText("Coarse");

    QRadioButton *verycoarse=new QRadioButton(GBX);
    verycoarse->setText("VeryCoarse");

    HLay->addWidget(precise);
    HLay->addWidget(coarse);
    HLay->addWidget(verycoarse);

    GBX->setLayout(HLay);

}
void Widget::currentDispaly(QWidget *w){
    //groupbox容器
    QGroupBox *GBX=new QGroupBox(w);
    GBX->setGeometry(QRect(100,250,350,150));
    GBX->setTitle("LCD Dispaly");

    //GBX->setStyleSheet("background-color:blue");
    //    水平布局
    QHBoxLayout *HLay=new QHBoxLayout(GBX);
    HLay->setSpacing(10);
    HLay->setContentsMargins(10,10,10,10);

    hour=new QLCDNumber(GBX);
    min=new QLCDNumber(GBX);
    sec=new QLCDNumber(GBX);


//    hour->setStyleSheet("color:white");
//    min->setStyleSheet("color:white");
//    sec->setStyleSheet("color:white");


    hour->setDigitCount(2);
    min->setDigitCount(2);
    sec->setDigitCount(2);

    HLay->addWidget(hour);
    HLay->addWidget(min);
    HLay->addWidget(sec);

    GBX->setLayout(HLay);
}
void Widget::startLcdTimer(){
    m_timer=new QTimer();
    m_timer->start();
    m_timer->setTimerType(Qt::CoarseTimer);

    singlebtn->setChecked(true);

    connect(m_timer,&QTimer::timeout,this,&Widget::lcdSlot);

}
void Widget::lcdSlot(){
    QTime time=QTime::currentTime();
    hour->display(time.hour());
    min->display(time.minute());
    sec->display(time.second());
}
