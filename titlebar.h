#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QtGui>

#define VALUE_DIS 5
//Const int  VALUE_DIS=5;
//枚举，按钮状态
enum eBtnMoustState{
     eBtnStateNone,//无效
     eBtnStateDefault,//默认值(如按钮初始显示)
     eBtnStateHover,//鼠标移到按钮上状态
     eBtnStatePress//鼠标按下按钮时状态
 };
class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    void CreateWidget();
    bool eventFilter(QObject *obj, QEvent *event);
    void CreateEventFiter();
	const QString GetBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/);
	void SetBtnIcon(QToolButton *pBtn,eBtnMoustState state,bool bInit/*=false*/);
	void CreateLayout();
	void SetWidgetStyle();
signals:
	void signal_min();
	void signal_maxrestore();
	void signal_close();

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

public slots:
	void slot_btnclick();
    void slot_btnpress();
private:
    bool m_bLeftButtonPressed;
    QPoint m_ptMove;
    QPoint m_ptPress;
    QLabel *m_pLabelIcon, *m_pLabelTitle, *m_pLabelVersion;
    QToolButton *m_pBtnSkin, *m_pBtnMenu, *m_pBtnMin, *m_pBtnMax, *m_pBtnClose;
    QHBoxLayout *m_pLayout;


};

#endif // TITLEBAR_H
