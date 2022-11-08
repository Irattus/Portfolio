#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H
#include <QGroupBox>
#include <QLayout>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include "Utilities/account.h"

class TransactionWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit TransactionWidget(QWidget * parent = nullptr);
    void setValue(std::shared_ptr<Account> const&,Transaction const&);
    void setMenu(QMenu*);
private:
    QMenu * m_menu;
    QLabel * m_amountLabel;
    QLabel * m_descriptionLabel;
    std::shared_ptr<Account> m_account;
    Transaction m_transaction;
signals:
    void removeTransactionWidget();
};

#endif // TRANSACTIONWIDGET_H
