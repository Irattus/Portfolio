#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "ui_transactiondialog.h"
#include "Utilities/account.h"
class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(QWidget *parent = nullptr);
    void createNew(Account const&  ac);
    void modify(Account const&  ac,Transaction const&);
signals:
    void newTransaction(Account const&,Transaction const&);
    void modifyTransaction(Account const&,Transaction const&);
private slots:
    void on_buttonBox_accepted();

private:
    bool m_status;
    Account m_account;
    Ui::TransactionDialog ui;
};

#endif // TRANSACTIONDIALOG_H
