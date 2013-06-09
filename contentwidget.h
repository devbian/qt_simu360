#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QtGui>

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    QLabel *m_pLabel;
    QVBoxLayout* m_pLayout;
};

#endif // CONTENTWIDGET_H
