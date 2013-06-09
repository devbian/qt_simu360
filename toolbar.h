#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QtGui/QLabel>
#include "mybtn.h"

class ToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0);
    void CreateWidget();
    void SetStyleSheet();
signals:
protected:
    virtual void resizeEvent(QResizeEvent *);

public slots:
    void slot_set(MyBtn *pObject);
private:
    QList<MyBtn*> m_listMyBtnPoint;
    QList<QString> m_listMyStr;
    QLabel *m_pLabel;
};

#endif // TOOLBAR_H
