#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QGroupBox>
#include <QList>
#include <QMenu>
#include <QAction>
#include "Utilities/account.h"
#include "transactionwidget.h"
#include "Dialogs/transactiondialog.h"
#include "Dialogs/accountdialog.h"

class AccountWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr);
    void setAccount(Account && a);
    void addTransAction(Transaction const&tr);
    void addTransActionWidget(Transaction &&tr);
    void removeTransaction(TransactionWidget*);

    inline void setAddAction(QAction * ac) { m_menu->addAction(ac); }
    inline void reload() { setTitle(m_account.name()+": "+m_account.totalS()); }

    inline Account account() const { return m_account; }

private slots:
    void modifyTransactions(Transaction const&);
    void on_AccountWidget_customContextMenuRequested(const QPoint &pos);
private:
    Account m_account;
    QList<TransactionWidget*> m_widgets;
    TransactionDialog * m_dialogTransaction;
    AccountDialog * m_dialogAccount;
    QMenu * m_menu;
    QAction * m_addTransAction;
    QAction * m_modifyAccount;
};

#endif // ACCOUNTWIDGET_H
