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
    void modify(QString const& name,Transaction const&);
signals:
    void newTransaction(Transaction const&);
    void modifyTransaction(Transaction const&);
private slots:
    void on_buttonBox_accepted();

private:
    bool m_status;
    Ui::TransactionDialog ui;
};

#endif // TRANSACTIONDIALOG_H
