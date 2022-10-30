#include "overallwidget.h"
OverallWidget::OverallWidget(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    m_scrollArea = new QScrollArea;
    m_accountContainer = new AccountWidgetContainer(m_scrollArea);
    layout()->addWidget(m_scrollArea);
    m_scrollArea->setWidget(m_accountContainer);

    connect(m_accountContainer,&AccountWidgetContainer::deleteAccount,this,&OverallWidget::RemoveAccount);
}

void OverallWidget::setBank(std::shared_ptr<Bank> bank)
{
    m_bank = bank;
    for(unsigned int i = 0; i< m_bank->accounts(); i++)
        m_accountContainer->addAccount(m_bank->getAccount(i));
}
