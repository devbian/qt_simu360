#include "mainframe.h"
#include "ui_mainframe.h"

MainFrame::MainFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MainFrame)
{

    ui->setupUi(this);
    initWindow();
    setWindowCircle();
    connectEvent();
}

void MainFrame::initWindow()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_pContentWidget = new ContentWidget(this);
    m_pStatusBar = new StatusBar(this);
    m_pTitleBar = new TitleBar(this);
    m_pToolBar = new ToolBar(this);
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->addWidget(m_pTitleBar);
    m_pMainLayout->addWidget(m_pToolBar);
    m_pMainLayout->addWidget(m_pContentWidget);
    m_pMainLayout->addWidget(m_pStatusBar);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(0,0,0,0);

    this->setStyleSheet("QFrame#MainFrame {border-image:url(:/res/images/frame.jpg); border:1px solid black;}");

    this->setMouseTracking(true);
    m_bLeftBtnPress = false;
    setMinimumWidth(850);
    setMinimumHeight(600);
    m_bMaxWin = false;

    this->m_pTitleBar->setMouseTracking(true);
    this->m_pContentWidget->setMouseTracking(true);
    m_bLeftBtnPress = false;
}

void MainFrame::setWindowCircle()
{
    //生成一张位图
    QBitmap objBitmap(size());
    //QPainter用于在位图上绘画
    QPainter painter(&objBitmap);
    //填充位图矩形框(用白色填充)
    painter.fillRect(rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    //在位图上画圆角矩形(用黑色填充)
    painter.drawRoundedRect(this->rect(),10,10);
    //使用setmask过滤即可
    setMask(objBitmap);
}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::connectEvent()
{
    connect(this->m_pTitleBar, SIGNAL(signal_close()), this, SLOT(close()));
}

void MainFrame::paintEvent(QPaintEvent *event)
{
    setWindowCircle();
}


void MainFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_ptPressGlobal = event->globalPos();
        m_bLeftBtnPress = true;
    }
}

void MainFrame::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_bLeftBtnPress)
    {
        m_eDirection = PointValid(event->x(),event->y());
        SetCursorStyle(m_eDirection);
    }
    else
    {
        int nXGlobal = event->globalX();
        int nYGlobal = event->globalY();
        SetDrayMove(nXGlobal,nYGlobal,m_eDirection);
        m_ptPressGlobal =QPoint(nXGlobal,nYGlobal);
    }
}

void MainFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftBtnPress = false;
        m_eDirection = eNone;
    }
}

void MainFrame::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= m_pTitleBar->height())
    {
        if(!m_bMaxWin)
        {
            m_rectRestoreWindow = geometry();
            setGeometry(qApp->desktop()->availableGeometry());
        }
        else
        {
            setGeometry(m_rectRestoreWindow);
        }
        m_bMaxWin = !m_bMaxWin;
    }
}

//确定点的位置方向
MainFrame::enum_Direction MainFrame::PointValid(int nXRelative,int nYRelative)
{
    int nTop = qAbs(nYRelative)<VALUE_DIS ?eTop:eNone;
    int nRight = qAbs(nXRelative-rect().right())<VALUE_DIS ? eRight:eNone;
    int nBottom = qAbs(nYRelative-rect().bottom())<VALUE_DIS ? eBottom:eNone;
    int nLeft = qAbs(nXRelative)<VALUE_DIS ? eLeft:eNone;
    return enum_Direction(nTop + nRight + nBottom + nLeft);
}

//设置鼠标样式
void MainFrame::SetCursorStyle(enum_Direction direction)
{
    //设置上下左右以及右上、右下、左上、坐下的鼠标形状
    switch(direction)
    {
    case eTop:
    case eBottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case eRight:
    case eLeft:
        setCursor(Qt::SizeHorCursor);
        break;
    case eTopRight:
    case eBottomLeft:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case eRightBottom:
    case eLeftTop:
        setCursor(Qt::SizeFDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}


//设置鼠标拖动的窗口位置信息
void MainFrame::SetDrayMove(int nXGlobal,int nYGlobal,enum_Direction direction)
{
    //计算偏差
    int ndX = nXGlobal - m_ptPressGlobal.x();
    int ndY = nYGlobal - m_ptPressGlobal.y();
    //获得主窗口位置信息
    QRect rectWindow = geometry();
    //判别方向
    if(direction & eTop)
    {
        rectWindow.setTop(rectWindow.top()+ndY);
    }
    if(direction & eRight)
    {
        rectWindow.setRight(rectWindow.right()+ndX);
    }
    if(direction & eBottom)
    {
        rectWindow.setBottom(rectWindow.bottom()+ndY);
    }
    if(direction & eLeft)
    {
        rectWindow.setLeft(rectWindow.left()+ndX);
    }
    if(rectWindow.width()< minimumWidth() || rectWindow.height()<minimumHeight())
    {
        return;
    }
    //重新设置窗口位置为新位置信息
    setGeometry(rectWindow);
}
