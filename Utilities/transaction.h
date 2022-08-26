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
    QDate m_time;
    qreal m_value;
    QString m_description;
    template<typename T>
    inline void print(T &strm) const
    {
        strm << QString::number(m_time.day()).toStdString().c_str()<< "-";
        strm << QString::number(m_time.month()).toStdString().c_str()<< "-";
        strm << QString::number(m_time.year()).toStdString().c_str()<< ":";
        strm << ( m_value > 0 ? "+": "");
        strm << m_value << ":";
        QStringList lst = m_description.split('\n');
        for(QString const& it: lst){
            strm<<it.toStdString().c_str();
        }
        strm<<'\n';
    }

};

#endif // TRANSACTION_H
