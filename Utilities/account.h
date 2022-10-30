#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDate>

struct Transaction
{
    QDate m_time;
    qreal m_value;
    QString m_description;
};

bool operator==(const Transaction& lhs, const Transaction& rhs)
{
    return (lhs.m_time == rhs.m_time) && (lhs.m_value == rhs.m_value) && (lhs.m_description == rhs.m_description);
}


class Account
{
public:
    Account(QString&& name);
    Account();

    void setName(QString&& name);

    void OrderTransactions();

    void addTransaction(Transaction &&tr);
    void addTransaction(Transaction const& tr);
    void removeTransaction(Transaction const&tr);
    void removeAt(unsigned int);

    qreal total() const;
    QString totalS() const;

    Transaction getTransaction(unsigned int) const;
    Transaction lastTransaction() const;
    inline unsigned int transactions() const { return m_transactions.size(); }
    QString name() const;




    template<typename T>
    friend T& operator<< (T& strm,Account  const & s) {
        s.print(strm);
        return strm;
    }

    template<typename T = QTextStream>
    friend T& operator>> (T& strm,Account const& s){
    s.read(strm);
    return strm;
    }

private:
    QVector<Transaction> m_transactions;
    QString m_name;

    template<typename T>
    inline void print (T& strm) const{
        strm << m_name;
        strm << m_transactions;
    }

    template<typename T>
    inline void read (T& strm) const{
        strm >> m_name;
        strm >> m_transactions;
    }


};

bool operator==(const Account& lhs, const Account& rhs)
{
    return lhs.name() == rhs.name();
}

#endif // ACCOUNT_H
