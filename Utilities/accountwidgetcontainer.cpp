#include "accountwidgetcontainer.h"

AccountWidgetContainer::AccountWidgetContainer(QWidget *parent) :
    QFrame(parent)
{
    ui.setupUi(this);
}

bool AccountWidgetContainer::NotAlreadyIn(std::shared_ptr<Account> ac)
{
    for(auto const& it :);
}
