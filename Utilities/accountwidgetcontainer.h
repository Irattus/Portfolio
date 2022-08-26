#ifndef ACCOUNTWIDGETCONTAINER_H
#define ACCOUNTWIDGETCONTAINER_H

#include "ui_accountwidgetcontainer.h"
#include "account.h"

class AccountWidgetContainer : public QFrame
{
    Q_OBJECT

public:
    explicit AccountWidgetContainer(QWidget *parent = nullptr);
    bool NotAlreadyIn(std::shared_ptr<Account>);
    void addAccount(std::shared_ptr<Account>);
    void removeAccount(std::shared_ptr<Account>);


private:
    Ui::AccountWidgetContainer ui;
};

#endif // ACCOUNTWIDGETCONTAINER_H
