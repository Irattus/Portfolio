#include "account.h"

Account::Account(QString&& name)
    :
      m_name(std::move(name))
{

}

Account::Account()
    :
      m_name("")
{

}

void Account::OrderTransactions()
{
    bool ordered = false;
    std::shared_ptr<Transaction> tmp;
    while(!ordered)
    for(unsigned int i=0; i<Transactions()-1;i++)
    {
        ordered = true;
        if(m_transactions[i]->date() < m_transactions[i+1]->date()){
            tmp = m_transactions[i+1];
            m_transactions[i+1] = m_transactions[i];
            m_transactions[i] = tmp;
            ordered = false;
        }
    }
}

void Account::SetName(QString&& name)
{
    m_name = std::move(name);
}

void Account::AddTransaction(std::shared_ptr<Transaction> && tr)
{
    m_transactions.push_back(std::move(tr));
}

void Account::AddTransaction(std::shared_ptr<Transaction> const& tr)
{
    m_transactions.push_back(tr);
}

void Account::RemoveTransaction(std::shared_ptr<Transaction> && tr)
{
    m_transactions.removeOne(std::move(tr));
}

void Account::RemoveAt(unsigned int index)
{
    m_transactions.removeAt(index);
}

std::shared_ptr<Transaction> Account::GetTransaction(unsigned int index) const
{
    return m_transactions.at(index);
}

std::shared_ptr<Transaction> Account::LastTransaction() const
{
    return m_transactions.last();
}

QString Account::Name() const
{
    return m_name;
}

qreal Account::Total() const
{
    qreal total = 0;
    for(auto const& it : m_transactions)
        total += it->value();
    return total;
}

QString Account::TotalS() const
{
    return QString::number(Total(),'f',2);
}
