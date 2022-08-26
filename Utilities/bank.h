#ifndef BANK_H
#define BANK_H
#include "account.h"


class Bank
{
public:
    inline void AddAccount(std::shared_ptr<Account> &&ac) { m_bank.push_back(std::move(ac)); }

    inline void RemoveAccount(std::shared_ptr<Account> const&ac) { m_bank.removeOne( std::move(ac) ); }

    inline unsigned int Accounts() const { return m_bank.size(); }

    inline std::shared_ptr<Account> GetAccount(unsigned int n) const { return m_bank[n]; }

    inline std::shared_ptr<Account> LastAccount() const { return m_bank.last(); }

    inline void Refs() const
    {
        for(auto const& it: m_bank){
            qDebug()<<"Account "<<it->Name()<<":"<<it.use_count();
            it->Refs();
        }
    }

    inline void OrderAccounts()
    {
        bool ordered = false;
        std::shared_ptr<Account> tmp;
        for(auto const& it: m_bank)
            it->OrderTransactions();
        while(!ordered)
        for(unsigned int i=0; i<Accounts()-1;i++)
        {
            ordered = true;

            if( m_bank[i]->LastTransaction()->date() < m_bank[i+1]->LastTransaction()->date()){
                tmp = m_bank[i+1];
                m_bank[i+1] = m_bank[i];
                m_bank[i] = tmp;
                ordered = false;
            }
        }
    }

    template<typename T = QTextStream>
    friend T& operator<< (T& strm,
    Bank const& s){
    s.print(strm);
    return strm;
    }

    Bank() = default;
private:
    QVector<std::shared_ptr<Account>> m_bank;

    template<typename T = QTextStream>
    inline void print (T& strm) const{
        for(auto const& it: m_bank)
            strm<<'\n'<<*it.get()<<'\n';
    }
};

#endif // BANK_H
