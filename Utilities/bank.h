#ifndef BANK_H
#define BANK_H
#include "account.h"


class Bank
{
public:
    inline void addAccount(Account &&ac) { m_bank.push_back(std::move(ac)); }

    inline void removeAccount(Account const& ac) { m_bank.removeOne( ac ); }

    inline unsigned int accounts() const { return m_bank.size(); }

    inline Account getAccount(unsigned int n) const { return m_bank[n]; }

    inline Account lastAccount() const { return m_bank.last(); }

    inline void OrderAccounts()
    {
        for(Account it: m_bank)
            it.OrderTransactions();
        std::sort(m_bank.begin(),m_bank.end(),[](Account a,Account b) -> bool
        {
            if(!a.transactions())
                return true;
            if(!b.transactions())
                return false;
            return (a.lastTransaction().m_time<b.lastTransaction().m_time);
        });
    }

    friend QDataStream& operator<< (QDataStream& strm,
    Bank const& s){
        strm<<s.m_bank;
    return strm;
    }

    friend QDataStream& operator>> (QDataStream& strm,
    Bank  s){
        strm>>s.m_bank;
    return strm;
    }

    Bank() = default;
private:
    QVector<Account> m_bank;
};



#endif // BANK_H
