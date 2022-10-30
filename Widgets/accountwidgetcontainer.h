#ifndef ACCOUNTWIDGETCONTAINER_H
#define ACCOUNTWIDGETCONTAINER_H

#include "Utilities/account.h"
#include "Widgets/accountwidget.h"

class AccountWidgetContainer : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWidgetContainer(QWidget *parent = nullptr);
    void addAccount(Account &&);
    void removeAccount(AccountWidget *);
signals:
    void deleteAccount(Account const&);

private:
};

#endif // ACCOUNTWIDGETCONTAINER_H
