#include "overallwidget.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

OverallWidget::OverallWidget(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    m_scrollArea = new QScrollArea;
    m_accountContainer = new AccountWidgetContainer(m_scrollArea);
    layout()->addWidget(m_scrollArea);
    m_scrollArea->setWidget(m_accountContainer);

    connect(m_accountContainer,&AccountWidgetContainer::DeleteAccount,this,&OverallWidget::RemoveAccount);
}

void OverallWidget::Load(QString &&text)
{
    QStringList lines = text.split('\n');
    QRegularExpression newAccount(R"(^\s*(\w*\s*?\w*)_\s*$)");
    QRegularExpression newTransaction(R"(^\s*(\d?\d)-(\d?\d)-(\d\d\d\d)\s*:\s*([+-]?)(\d*\.?\d+)\s*:?\s*([\w*\s*?\w*]*)?$)");
    QRegularExpressionMatch match;
    std::shared_ptr<Account> tmp = nullptr;
    for( QString const& it : lines){
        if( match = newAccount.match(it) ,match.hasMatch())
        {
            if(tmp != nullptr)
                m_bank->AddAccount( std::move(tmp) );
            tmp = std::make_shared<Account>(Account(match.captured(1)));
        }
        else if( match = newTransaction.match(it), match.hasMatch())
        {
            QDate date;
            date.setDate(match.captured(3).toUInt(),match.captured(2).toUInt(),match.captured(1).toUInt());
            qreal value;
            value = match.captured(5).toDouble();
            if(!(match.captured(4).isEmpty() || match.captured(4) == "+"))
                value = - value;
            QString desc = match.captured(6);
            tmp->AddTransaction(std::make_shared<Transaction>(Transaction(std::move(date),std::move(value),std::move(desc))));
        }
    }
    if(tmp != nullptr)
        m_bank->AddAccount( std::move(tmp) );
    for(unsigned int i = 0; i < m_bank->Accounts() ; i++)
        m_accountContainer->AddAccount( m_bank->GetAccount(i) );
}
