#include "accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QGroupBox(parent)
{
    setLayout(new QVBoxLayout(this));
    m_transactionContainer = new WidgetContainer(this);
    layout()->addWidget(m_transactionContainer);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,&AccountWidget::customContextMenuRequested, this, &AccountWidget::on_AccountWidget_customContextMenuRequested);

}

void AccountWidget::addTransActionWidget(Transaction const& tr)
{
    /*TransactionWidget * tmp = new TransactionWidget(this);
    tmp->setTransaction(m_account.name(),std::move(tr));
    connect(tmp,&TransactionWidget::removeTransaction,this,&AccountWidget::removeTransaction);
    connect(tmp,&TransactionWidget::modifyTransaction,m_dialogTransaction,&TransactionDialog::modify);
    tmp->setAddAction(m_addTransAction);
    layout()->addWidget(tmp);
    m_widgets.append(tmp);*/
    reload();
}
/*
void AccountWidget::modifyTransactions(Transaction const& tr)
{
    for(TransactionWidget * it: m_widgets)
        if(it->transaction()==tr)
            it->reload();
    reload();
}


void AccountWidget::removeTransaction(TransactionWidget* widget)
{
    m_account.removeTransaction(widget->transaction());
    layout()->removeWidget(widget);
    m_widgets.removeOne(widget);
    delete widget;
    reload();
}
*/
void AccountWidget::setAccount(Account const& a)
{
    m_account = a;
    for(unsigned int i=0; i < m_account.transactions(); i++)
        addTransActionWidget(m_account.getTransaction(i));
}

void AccountWidget::on_AccountWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menu->exec(mapToGlobal(pos),nullptr);
}

