#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QPair>
#include <QDateTime>
#include <iostream>

class Transaction
{
public:
    Transaction(QDate &&,qreal &&,QString &&);
    Transaction(Transaction const&);
    Transaction(Transaction&&);

    void changeDescription(QString const& text);
    void changeDate(QDate const& text);
    void changeAmount(qreal const& text);

    QDate date() const;
    qreal value() const;
    QString valueS() const;
    QString description() const;

    template<typename T>
    friend T& operator<< (T& strm,Transaction const& s) {
        s.print(strm);
        return strm;
    }


private:

    template<typename T>
    inline void print(T &strm) const
    {
        strm << m_time;
        strm << m_value;
        strm << m_description;
    }

};

#endif // TRANSACTION_H
