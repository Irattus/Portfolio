#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QGroupBox>
#include <QList>
#include <QMenu>
#include <QAction>
#include "Utilities/account.h"
#include "widgetcontainer.h"

class AccountWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr);
    void setMenu(QMenu * menu);
    void setAccount(std::shared_ptr<Account> const& a);
    void addTransActionWidget(Transaction const&tr);

    inline void reload() { setTitle(m_account->name()+": "+m_account->totalS()); }

    inline std::shared_ptr<Account> account() const { return m_account; }

private slots:
    void on_AccountWidget_customContextMenuRequested(const QPoint &pos);
private:
    std::shared_ptr<Account> m_account;
    WidgetContainer * m_transactionContainer;
    QMenu * m_menu;


    //TransactionDialog * m_dialogTransaction;

    //QAction * m_addTransAction;
    //QAction * m_modifyAccount;
};

#endif // ACCOUNTWIDGET_H
