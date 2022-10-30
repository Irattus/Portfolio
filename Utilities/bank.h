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
        bool ordered = false;
        Account tmp;
        for(Account it: m_bank)
            it.OrderTransactions();
        while(!ordered)
        for(unsigned int i=0; i<accounts()-1;i++)
        {
            ordered = true;

            if( m_bank[i].lastTransaction().m_time < m_bank[i+1].lastTransaction().m_time){
                tmp = m_bank[i+1];
                m_bank[i+1] = m_bank[i];
                m_bank[i] = tmp;
                ordered = false;
            }
        }
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
