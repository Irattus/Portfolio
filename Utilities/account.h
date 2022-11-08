#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDate>
#include <QObject>

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
    Account(QString const& name);
    Account();

    void setName(QString const& name);

    void OrderTransactions();

    void addTransaction(Transaction const& tr);
    inline void appendTransaction(QVector<Transaction> const& tr) { m_transactions.append(tr); }
    inline QVector<Transaction> allTransactions() const { return m_transactions; }
    void modifyTransaction(Transaction const& source, Transaction const& dest);
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

    friend QDataStream &operator<<(QDataStream & out, const std::shared_ptr<Account> & ac)
    {
        out<<ac->m_name;
        out<<ac->m_transactions;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in , std::shared_ptr<Account> &ac)
    {
        QString tmpText;
        QVector<Transaction> tmpTransactionVector;
        in>>tmpText;
        in>>tmpTransactionVector;
        ac = std::make_shared<Account>(Account(tmpText));
        for(Transaction const& it: tmpTransactionVector)
            ac->addTransaction(it);
        return in;
    }

private:
    QVector<Transaction> m_transactions;
    QString m_name;


};

bool operator==(const Account& lhs, const Account& rhs);



#endif // ACCOUNT_H
