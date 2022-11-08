#ifndef BANK_H
#define BANK_H
#include "account.h"


class Bank
{
public:
    inline void addAccount(std::shared_ptr<Account> const& ac) { m_bank.append(ac); }

    inline void removeAccount(std::shared_ptr<Account> const& ac) { m_bank.removeOne( ac ); }

    inline unsigned int accounts() const { return m_bank.size(); }

    inline std::shared_ptr<Account> getAccount(unsigned int n) const { return m_bank[n]; }

    inline std::shared_ptr<Account> lastAccount() const { return m_bank.last(); }

    inline QVector<std::shared_ptr<Account>> allAccounts() const { return m_bank; }

    inline void OrderAccounts()
    {
        for(std::shared_ptr<Account> it: m_bank)
            it->OrderTransactions();
        std::sort(m_bank.begin(),m_bank.end(),[](std::shared_ptr<Account> a,std::shared_ptr<Account> b) -> bool
        {
            if(!a->transactions())
                return false;
            if(!b->transactions())
                return true;
            return (a->lastTransaction().m_time<b->lastTransaction().m_time);
        });
    }

    friend QDataStream& operator<< (QDataStream& strm,
    Bank const& s){
        strm<<s.m_bank;
    return strm;
    }

    friend QDataStream& operator>> (QDataStream& strm,
    Bank & s){
        QVector<std::shared_ptr<Account>> tmp;
        strm>>tmp;
        s.m_bank = tmp;
    return strm;
    }

    friend QDataStream& operator<< (QDataStream& strm,
    std::shared_ptr<Bank> const& s){
        strm<<s->m_bank;
    return strm;
    }

    Bank() = default;
private:
    QVector<std::shared_ptr<Account>> m_bank;
};



#endif // BANK_H
