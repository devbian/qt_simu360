#include "contentwidget.h"

ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedHeight(50);
    m_pLabel = new QLabel();
    m_pLabel->setText(tr("text lalala"));
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->addWidget(m_pLabel);
    this->setLayout(m_pLayout);
    m_pLabel->setStyleSheet("");
}
