#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDate>

struct Transaction
{
    QDate m_time;
    qreal m_value;
    QString m_description;
};

QDataStream &operator<<(QDataStream & out, const Transaction & tr);
QDataStream &operator>>(QDataStream &in , Transaction &tr);

bool operator==(const Transaction& lhs, const Transaction& rhs);


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

    friend QDataStream &operator<<(QDataStream & out, const Account & ac)
    {
        out<<ac.m_name;
        out<<ac.m_transactions;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in , Account &ac)
    {
        in>>ac.m_name;
        in>>ac.m_transactions;
        return in;
    }

private:
    QVector<Transaction> m_transactions;
    QString m_name;


};

bool operator==(const Account& lhs, const Account& rhs);



#endif // ACCOUNT_H
