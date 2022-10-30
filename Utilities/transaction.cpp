#include "transaction.h"


Transaction::Transaction(QDate && time,qreal && val,QString && str)
    : m_time(std::move(time)),
      m_value(std::move(val)),
      m_description(std::move(str))
{
}

Transaction::Transaction(Transaction const& tr)
    : m_time(tr.date()),
      m_value(tr.value()),
      m_description(tr.description())
{
}



Transaction::Transaction(Transaction && tr)
    : m_time(tr.date()),
      m_value(tr.value()),
      m_description(tr.description())
{
}

QString Transaction::description() const
{
    return m_description;
}

void Transaction::changeDescription(QString const& text)
{
     m_description = text;
}

void Transaction::changeDate(QDate const& time)
{
    m_time = time;
}

void Transaction::changeAmount(qreal const& val)
{
    m_value = val;
}

QDate Transaction::date() const
{
    return m_time;
}

qreal Transaction::value() const
{
    return m_value;
}

QString Transaction::valueS() const
{
    return QString::number(m_value,'f',2);
}



