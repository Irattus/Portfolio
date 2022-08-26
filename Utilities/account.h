#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "transaction.h"

class Account
{
public:
    Account(QString&& name);
    Account();

    void SetName(QString&& name);

    void OrderTransactions();

    void AddTransaction(std::shared_ptr<Transaction> &&tr);
    void AddTransaction(std::shared_ptr<Transaction> const& tr);
    void RemoveTransaction(std::shared_ptr<Transaction> &&tr);
    void RemoveAt(unsigned int);

    qreal Total() const;
    QString TotalS() const;

    std::shared_ptr<Transaction> GetTransaction(unsigned int) const;
    std::shared_ptr<Transaction> LastTransaction() const;
    inline unsigned int Transactions() const { return m_transactions.size(); }
    QString Name() const;

    inline void Refs() const
    {   for(auto const& it: m_transactions)
            qDebug()<<"Trans "<<it->valueS()<<":"<<it.use_count();  }


    template<typename T>
    friend T& operator<< (T& strm,Account  const & s) {
        s.print(strm);
        return strm;
    }

private:
    QVector<std::shared_ptr<Transaction>> m_transactions;
    QString m_name;

    template<typename T>
    inline void print (T& strm) const{
        strm <<m_name.toStdString().c_str()<<"_\n";
        for (int i = 0 ; i < m_transactions.size(); i++)
            strm << *m_transactions[i].get();
    }

};

#endif // ACCOUNT_H
