#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H
#include <QGroupBox>
#include <QLayout>
#include <QLabel>
#include "Utilities/account.h"

class TransactionWidget : public QGroupBox
{
public:
    explicit TransactionWidget(QWidget * parent = nullptr);
    void setValue(std::shared_ptr<Account> const&,Transaction const&);
private:
    QLabel * m_amountLabel;
    QLabel * m_descriptionLabel;
    std::shared_ptr<Account> m_account;
    Transaction m_transaction;
};

#endif // TRANSACTIONWIDGET_H
