#include "accountwidgetcontainer.h"

AccountWidgetContainer::AccountWidgetContainer(QWidget *parent) :
    QFrame(parent)
{
    ui.setupUi(this);
}

void AccountWidgetContainer::AddAccount(std::shared_ptr<Account> &&ac)
{
    AccountWidget * tmp = new AccountWidget(this);
    tmp->SetAccount( std::move(ac) );
    QAction * act = new QAction("Remove Account",tmp);
    connect(act,&QAction::triggered,this,[this,tmp](){RemoveAccount(tmp);});
    tmp->SetAddAction(act);
    ui.verticalLayout->addWidget(tmp);
    tmp->reload();
}

void AccountWidgetContainer::RemoveAccount( AccountWidget * tmp )
{
    emit DeleteAccount(tmp->account());
    ui.verticalLayout->removeWidget(tmp);
    delete tmp;
}

bool AccountWidgetContainer::NotAlreadyIn(std::shared_ptr<Account> &&ac)
{
    for(auto const& it : ui.verticalLayout->children())
        if(ac == qobject_cast<AccountWidget*>(it)->account())
            return false;
    return true;
}
