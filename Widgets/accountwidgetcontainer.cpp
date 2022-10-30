#include "accountwidgetcontainer.h"
#include <QVBoxLayout>

AccountWidgetContainer::AccountWidgetContainer(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    setMinimumSize(QSize(parent->width(),parent->height()));
}

void AccountWidgetContainer::addAccount(Account &&ac)
{
    AccountWidget * tmp = new AccountWidget(this);
    tmp->setAccount( std::move(ac) );
    QAction * act = new QAction("Remove Account",tmp);
    connect(act,&QAction::triggered,this,[this,tmp](){removeAccount(tmp);});
    tmp->setAddAction(act);
    layout()->addWidget(tmp);
    tmp->reload();
}

void AccountWidgetContainer::removeAccount( AccountWidget * tmp )
{
    emit deleteAccount(tmp->account());
    layout()->removeWidget(tmp);
    delete tmp;
}

