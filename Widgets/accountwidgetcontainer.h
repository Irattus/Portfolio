#ifndef ACCOUNTWIDGETCONTAINER_H
#define ACCOUNTWIDGETCONTAINER_H

#include "ui_accountwidgetcontainer.h"
#include "Utilities/account.h"
#include "Widgets/accountwidget.h"

class AccountWidgetContainer : public QFrame
{
    Q_OBJECT

public:
    explicit AccountWidgetContainer(QWidget *parent = nullptr);
    bool NotAlreadyIn(std::shared_ptr<Account> &&);
    void AddAccount(std::shared_ptr<Account> &&);
    void RemoveAccount(AccountWidget *);
signals:
    void DeleteAccount(std::shared_ptr<Account> const&);

private:
    Ui::AccountWidgetContainer ui;
};

#endif // ACCOUNTWIDGETCONTAINER_H
