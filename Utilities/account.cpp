#include "account.h"


QDataStream &operator<<(QDataStream & out, const Transaction & tr)
{
    out<<tr.m_time;
    out<<tr.m_value;
    out<<tr.m_description;
    return out;
}

QDataStream &operator>>(QDataStream &in , Transaction &tr)
{
    in>>tr.m_time;
    in>>tr.m_value;
    in>>tr.m_description;
    return in;
}
bool operator==(const Transaction& lhs, const Transaction& rhs){
    return (lhs.m_time == rhs.m_time) && (lhs.m_value == rhs.m_value) && (lhs.m_description == rhs.m_description);
}

bool operator==(const Account& lhs, const Account& rhs)
{
    return lhs.name() == rhs.name();
}

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
    std::sort(m_transactions.begin(),m_transactions.end(),[](Transaction a,Transaction b) -> bool
    { return a.m_time<b.m_time;});
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
