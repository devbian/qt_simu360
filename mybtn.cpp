#include "mybtn.h"
const int TOOLICON_WH=48;
const int TOOLWIDGET_W=70;
const int TOOLWIDGET_H=80;
MyBtn::MyBtn(const QString &strImage,const QString &strInfo,QWidget *parent):
    QToolButton(parent),
    m_bOver(false),
    m_bPress(false),
    m_strImage(strImage),
    m_strInfo(strInfo)
{
    //文本颜色
    QPalette objPalette = palette();
    objPalette.setColor(QPalette::ButtonText, QColor(220,220,220));
    setPalette(objPalette);
     //文本粗体
    QFont &objFont = const_cast<QFont &>(font());
    objFont.setWeight(QFont::Bold);
    //样式
    setStyleSheet("QToolButton{border:0px;}");
    //大小
    setIconSize(QSize(TOOLICON_WH,TOOLICON_WH));
    resize(TOOLWIDGET_W,TOOLWIDGET_H);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //设置图像文本
    setIcon(QPixmap(strImage));
    setText(strInfo);
    //连接press信号槽，表示按钮按下时
    connect(this,SIGNAL(pressed()),this,SLOT(slot_pressed()));

}


//enterEvent--鼠标移到按钮上事件
void MyBtn::enterEvent(QEvent *event)
{
    SetOver(true);
}
//leaveEvent--鼠标离开按钮事件
void MyBtn::leaveEvent(QEvent *event)
{
    SetOver(false);
}
//SetOver
void MyBtn::SetOver(bool bEnable)
{
    if(bEnable!=m_bOver)
    {
        //设置m_bOver标志位
        m_bOver = bEnable;
        //更新
        update();
    }
}

//slot_pressed--槽函数
void MyBtn::slot_pressed()
{
    SetPress(true);
    emit signal_parent(this);
}

//SetPress
void MyBtn::SetPress(bool bEnable)
{
    if(bEnable!=m_bPress)
    {
        //设置m_bOver标志位
        m_bPress = bEnable;
        //更新
        update();
    }
}

//重绘事件
void MyBtn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //如果按钮被按下
    if(m_bPress)
    {
        //绘制被按下时的效果
        painterinfo(150,200,&painter);
    }
    else if(m_bOver)//如果按钮没有被按下并且鼠标移到按钮上
    {
        //绘制鼠标移到按钮上的按钮效果
        painterinfo(50,100,&painter);
    }
    //调用基类的重绘事件以显示图像文本等
    QToolButton::paintEvent(event);
}
//绘制背景渐变
void MyBtn::painterinfo(int nTopPartOpacity,int nBottomPartOpacity,QPainter *pPainter)
{
    //设置画笔
    QPen objPen(Qt::NoBrush,1);
    pPainter->setPen(objPen);
    //设置渐变画刷
    QLinearGradient objLinear(rect().topLeft(),rect().bottomLeft());
    //顶部颜色和透明度
    objLinear.setColorAt(0,QColor(150,150,150,nTopPartOpacity));
    //中间颜色和透明度
    objLinear.setColorAt(0.5,QColor(50,50,50,255));
    //底部颜色和透明度
    objLinear.setColorAt(1,QColor(100,100,100,nBottomPartOpacity));
    QBrush objBrush(objLinear);
    pPainter->setBrush(objBrush);
    //画圆角矩形
    pPainter->drawRoundedRect(rect(),5,5);
}
