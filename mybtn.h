#ifndef MYBTN_H
#define MYBTN_H

#include <QToolButton>
#include <QtGui/QPainter>

class MyBtn : public QToolButton
{
    Q_OBJECT
public:
    explicit MyBtn(const QString &strImage,const QString &strInfo,QWidget *parent);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void SetOver(bool bEnable);
    void SetPress(bool bEnable);
    void paintEvent(QPaintEvent *event);
    void painterinfo(int nTopPartOpacity,int nBottomPartOpacity,QPainter *pPainter);
signals:
    void signal_parent(MyBtn *);
public slots:
    void slot_pressed();
private:
    bool m_bOver, m_bPress;
    QString m_strImage, m_strInfo;
};

#endif // MYBTN_H
