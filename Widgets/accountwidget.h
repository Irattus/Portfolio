#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include "ui_accountwidget.h"
#include "Utilities/account.h"
#include <QList>
#include <QMenu>
#include <QAction>
#include "transactionwidget.h"
#include "Dialogs/transactiondialog.h"
#include "Dialogs/accountdialog.h"

class AccountWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr);
    void SetAccount(std::shared_ptr<Account> && a);
    void AddTransAction(std::shared_ptr<Transaction> const&tr);
    void AddTransActionWidget(std::shared_ptr<Transaction> &&tr);
    void RemoveTransaction(TransactionWidget*);

    inline void SetAddAction(QAction * ac) { m_menu->addAction(ac); }
    inline void reload() { setTitle(m_account->Name()+": "+m_account->TotalS()); }

    inline std::shared_ptr<Account> account() const { return m_account; }

private slots:
    void ModifyTransactions(std::shared_ptr<Transaction> const&);
    void on_AccountWidget_customContextMenuRequested(const QPoint &pos);
private:
    Ui::AccountWidget ui;
    std::shared_ptr<Account> m_account;
    QList<TransactionWidget*> m_widgets;
    TransactionDialog * m_dialogTransaction;
    AccountDialog * m_dialogAccount;
    QMenu * m_menu;
    QAction * m_addTransAction;
    QAction * m_modifyAccount;
};

#endif // ACCOUNTWIDGET_H
