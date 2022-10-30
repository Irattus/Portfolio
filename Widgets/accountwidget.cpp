#include "accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QGroupBox(parent),
    m_dialogTransaction(new TransactionDialog(this)),
    m_dialogAccount(new AccountDialog(this)),
    m_menu(new QMenu(this)),
    m_addTransAction(new QAction("Add Transaction",m_menu)),
    m_modifyAccount(new QAction("Modify Account",m_menu))
{
    setLayout(new QVBoxLayout(this));


    setContextMenuPolicy(Qt::CustomContextMenu);
    m_menu->addAction(m_addTransAction);
    m_menu->addAction(m_modifyAccount);
    connect(this,&AccountWidget::customContextMenuRequested, this, &AccountWidget::on_AccountWidget_customContextMenuRequested);
    connect(m_addTransAction,&QAction::triggered,m_dialogTransaction,[this](){m_dialogTransaction->createNew(m_account.name());});
    connect(m_dialogTransaction,&TransactionDialog::newTransaction, this,&AccountWidget::addTransAction);
    connect(m_dialogTransaction,&TransactionDialog::modifyTransaction,this,&AccountWidget::modifyTransactions);
    connect(m_modifyAccount,&QAction::triggered,this,[this](){m_dialogAccount->ModifyAccount(m_account.name());});
    connect(m_dialogAccount,&AccountDialog::changeAccount,this,
    [this](QString name)
    {
        m_account.setName(std::move(name));
        reload();
    });
}


void AccountWidget::addTransAction(Transaction const& tr)
{
    m_account.addTransaction( tr );
    addTransActionWidget( m_account.lastTransaction() );
}

void AccountWidget::addTransActionWidget(Transaction && tr)
{
    TransactionWidget * tmp = new TransactionWidget(this);
    tmp->setTransaction(m_account.name(),std::move(tr));
    connect(tmp,&TransactionWidget::removeTransaction,this,&AccountWidget::removeTransaction);
    connect(tmp,&TransactionWidget::modifyTransaction,m_dialogTransaction,&TransactionDialog::modify);
    tmp->setAddAction(m_addTransAction);
    layout()->addWidget(tmp);
    m_widgets.append(tmp);
    reload();
}

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

void AccountWidget::setAccount(Account &&a)
{
    m_account = a;
    for(unsigned int i=0; i < m_account.transactions(); i++)
        addTransActionWidget(m_account.getTransaction(i));
}

void AccountWidget::on_AccountWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menu->exec(mapToGlobal(pos),nullptr);
}

