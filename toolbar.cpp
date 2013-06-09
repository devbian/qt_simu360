#include "toolbar.h"
#include <QtGui>
const int WIDGET_CNT=9;
const int TOOLWIDGET_H=75;
const int VALUE_DIS=5;
ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent)
{
    CreateWidget();
    SetStyleSheet();
}

void ToolBar::CreateWidget()
{
    //文本例子
    m_listMyStr<<"Examine"<<"KillTrojan"<<"CleanDust"<<"LeakRepair"<<"SysRepair"
              <<"CleanCom"<<"FunFull"<<"SoftMan"<<"Phnix";
    //创建toolbutton
    for(int nIndex = 0;nIndex<WIDGET_CNT;++nIndex)
    {
        //图像资源路径
        QString strImage = QString(":/res/images/%1.png").arg(nIndex+1);
        //创建自定义QToolButton(MyBtn)
        m_listMyBtnPoint.append(new MyBtn(strImage,m_listMyStr[nIndex],this));
        //设置toolbutton的位置
        m_listMyBtnPoint.at(nIndex)->move(nIndex*TOOLWIDGET_H+VALUE_DIS,0);
        //该信号槽设置其他按钮的按下状态bool值
        connect(m_listMyBtnPoint.at(nIndex),
                SIGNAL(signal_parent(MyBtn*)),
                this,SLOT(slot_set(MyBtn*)));
    }
    //创建label
    m_pLabel = new QLabel(this);
    m_pLabel->setPixmap(QPixmap(":/res/images/logo.png"));
}


//resizeEvent
void ToolBar::resizeEvent (QResizeEvent * event)
{
    qDebug() << "proccessing logo label...";
    //按钮垂直居中
    //    m_pLabel->move(rect().width()-m_pLabel->pixmap()->width()-VALUE_DIS,
    //                   (rect().height()-m_pLabel->pixmap()->height())/2 );
    m_pLabel->move(rect().width()-m_pLabel->pixmap()->width()-VALUE_DIS,
                   0);
}

//槽函数
void ToolBar::slot_set(MyBtn *pObject)
{
    for(int nIndex = 0;nIndex<WIDGET_CNT;++nIndex)
    {
        if(m_listMyBtnPoint.at(nIndex)!=pObject)
        {
            m_listMyBtnPoint.at(nIndex)->SetPress(false);
        }
    }
}

void ToolBar::SetStyleSheet()
{
//    setStyleSheet("QLabel{border:2px solid red;}");
        setStyleSheet("QLabel{border:0px;}");
}
