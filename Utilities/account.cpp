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
    Transaction tmp;
    while(!ordered)
    for(unsigned int i=0; i<transactions()-1;i++)
    {
        ordered = true;
        if(m_transactions[i].m_time < m_transactions[i+1].m_time){
            tmp = m_transactions[i+1];
            m_transactions[i+1] = m_transactions[i];
            m_transactions[i] = tmp;
            ordered = false;
        }
    }
}

void Account::setName(QString&& name)
{
    m_name = std::move(name);
}

void Account::addTransaction(Transaction && tr)
{
    m_transactions.push_back(std::move(tr));
}

void Account::addTransaction(Transaction const& tr)
{
    m_transactions.push_back(tr);
}

void Account::removeTransaction(Transaction const& tr)
{
    m_transactions.removeOne(tr);
}

void Account::removeAt(unsigned int index)
{
    m_transactions.removeAt(index);
}

Transaction Account::getTransaction(unsigned int index) const
{
    return m_transactions.at(index);
}

Transaction Account::lastTransaction() const
{
    return m_transactions.last();
}

QString Account::name() const
{
    return m_name;
}

qreal Account::total() const
{
    qreal total = 0;
    for(auto const& it : m_transactions)
        total += it.m_value;
    return total;
}

QString Account::totalS() const
{
    return QString::number(total(),'f',2);
}
