#ifndef ACCOUNTWIDGETCONTAINER_H
#define ACCOUNTWIDGETCONTAINER_H

#include "Utilities/account.h"
#include "Widgets/accountwidget.h"

class AccountWidgetContainer : public QWidget
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
};

#endif // ACCOUNTWIDGETCONTAINER_H
