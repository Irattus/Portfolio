#include "accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QGroupBox(parent),
    m_dialogTransaction(new TransactionDialog(this)),
    m_dialogAccount(new AccountDialog(this)),
    m_menu(new QMenu(this)),
    m_addTransAction(new QAction("Add Transaction",m_menu)),
    m_modifyAccount(new QAction("Modify Account",m_menu))
{
    ui.setupUi(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    m_menu->addAction(m_addTransAction);
    m_menu->addAction(m_modifyAccount);
    connect(m_addTransAction,&QAction::triggered,m_dialogTransaction,[this](){m_dialogTransaction->createNew(m_account->Name());});
    connect(m_dialogTransaction,&TransactionDialog::NewTransaction, this,&AccountWidget::AddTransAction);
    connect(m_dialogTransaction,&TransactionDialog::ModifyTransaction,this,&AccountWidget::ModifyTransactions);
    connect(m_modifyAccount,&QAction::triggered,this,[this](){m_dialogAccount->ModifyAccount(m_account->Name());});
    connect(m_dialogAccount,&AccountDialog::ChangeAccount,this,
    [this](QString name)
    {
        m_account->SetName(std::move(name));
        reload();
    });
}


void AccountWidget::AddTransAction(std::shared_ptr<Transaction> const& tr)
{
    m_account->AddTransaction( std::move(tr) );
    AddTransActionWidget( m_account->LastTransaction() );
}

void AccountWidget::AddTransActionWidget(std::shared_ptr<Transaction> && tr)
{
    TransactionWidget * tmp = new TransactionWidget(ui.Container);
    tmp->setTransaction(m_account->Name(),std::move(tr));
    connect(tmp,&TransactionWidget::RemoveTransaction,this,&AccountWidget::RemoveTransaction);
    connect(tmp,&TransactionWidget::ModifyTransaction,m_dialogTransaction,&TransactionDialog::modify);
    tmp->setAddAction(m_addTransAction);
    ui.vLayout->addWidget(tmp);
    m_widgets.append(tmp);
    reload();
}

void AccountWidget::ModifyTransactions(std::shared_ptr<Transaction> const& tr)
{
    for(TransactionWidget * it: m_widgets)
        if(it->transaction()==tr)
            it->reload();
    reload();
}


void AccountWidget::RemoveTransaction(TransactionWidget* widget)
{
    m_account->RemoveTransaction(widget->transaction());
    ui.vLayout->removeWidget(widget);
    m_widgets.removeOne(widget);
    delete widget;
    reload();
}

void AccountWidget::SetAccount(std::shared_ptr<Account> &&a)
{
    m_account = std::move(a);
    for(unsigned int i=0; i < m_account->Transactions(); i++)
        AddTransActionWidget(m_account->GetTransaction(i));
}

void AccountWidget::on_AccountWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menu->exec(mapToGlobal(pos),nullptr);
}

