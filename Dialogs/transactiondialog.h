#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "ui_transactiondialog.h"
#include "Utilities/account.h"
class TransactionDialog : public QDialog
{
    Q_OBJECT
//Non tocca lo shared ptr qui , altrimenti non ci capisco più na sega
public:
    explicit TransactionDialog(QWidget *parent = nullptr);
    void createNew(std::shared_ptr<Account> const&  ac);
    void modify(std::shared_ptr<Account> const&  ac,Transaction const&);
signals:
    void newTransaction(Transaction const&);
    void modifyTransaction(std::shared_ptr<Account> const&,Transaction const&);
private slots:
    void on_buttonBox_accepted();

private:
    bool m_status;
    std::shared_ptr<Account> m_account;
    Ui::TransactionDialog ui;
};

#endif // TRANSACTIONDIALOG_H
