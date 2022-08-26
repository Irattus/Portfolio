#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "ui_transactiondialog.h"
#include "Utilities/account.h"
class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(QWidget *parent = nullptr);
    void createNew(QString&& name);
    void modify(QString const& name,std::shared_ptr<Transaction> const&);
signals:
    void NewTransaction(std::shared_ptr<Transaction> const&);
    void ModifyTransaction(std::shared_ptr<Transaction> const&);
private slots:
    void on_buttonBox_accepted();

private:
    std::shared_ptr<Transaction> m_transaction;
    bool m_status;
    Ui::TransactionDialog ui;
};

#endif // TRANSACTIONDIALOG_H
