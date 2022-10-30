#include "accountwidgetcontainer.h"
#include <QVBoxLayout>

AccountWidgetContainer::AccountWidgetContainer(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    setMinimumSize(QSize(parent->width(),parent->height()));
}

void AccountWidgetContainer::AddAccount(std::shared_ptr<Account> &&ac)
{
    AccountWidget * tmp = new AccountWidget(this);
    tmp->setAccount( std::move(ac) );
    QAction * act = new QAction("Remove Account",tmp);
    connect(act,&QAction::triggered,this,[this,tmp](){RemoveAccount(tmp);});
    tmp->setAddAction(act);
    layout()->addWidget(tmp);
    tmp->reload();
}

void AccountWidgetContainer::RemoveAccount( AccountWidget * tmp )
{
    emit DeleteAccount(tmp->account());
    layout()->removeWidget(tmp);
    delete tmp;
}

bool AccountWidgetContainer::NotAlreadyIn(std::shared_ptr<Account> &&ac)
{
    for(auto const& it : layout()->children())
        if(ac == qobject_cast<AccountWidget*>(it)->account())
            return false;
    return true;
}
