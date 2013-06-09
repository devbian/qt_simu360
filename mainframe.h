#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include "contentwidget.h"
#include "statusbar.h"
#include "titlebar.h"
#include "toolbar.h"
#include <QtGui>

namespace Ui {
class MainFrame;
}

class MainFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();
    void connectEvent();

    enum enum_Direction
    {
        eNone,
        eTop = 1,
        eRight =2 ,
        eBottom =4,
        eLeft = 8,
        eTopRight = eTop + eRight,
        eRightBottom = eRight + eBottom,
        eBottomLeft = eBottom + eLeft,
        eLeftTop = eLeft + eTop
    };

    void paintEvent(QPaintEvent *);
//    static MainFrame *Instance();
//    static MainFrame *mainFrameInstance;

protected:
        virtual void mousePressEvent(QMouseEvent *);
        virtual void mouseReleaseEvent(QMouseEvent *);
        virtual void mouseMoveEvent(QMouseEvent *);
        virtual void mouseDoubleClickEvent(QMouseEvent *event);
private:
    void initWindow();
    void setWindowCircle();
    void SetCursorStyle(enum_Direction direction);
    void SetDrayMove(int nXGlobal,int nYGlobal,enum_Direction direction);
    enum_Direction PointValid(int nXRelative,int nYRelative);
    Ui::MainFrame *ui;
    TitleBar *m_pTitleBar;
    ContentWidget *m_pContentWidget;
    ToolBar *m_pToolBar;
    StatusBar *m_pStatusBar;
    QVBoxLayout *m_pMainLayout;
    enum_Direction m_eDirection;
    QPoint m_ptPressGlobal;
    bool m_bLeftBtnPress;
    bool m_bMaxWin;
    QRect m_rectRestoreWindow;
};

#endif // MAINFRAME_H
