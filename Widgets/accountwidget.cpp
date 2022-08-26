#include "accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QGroupBox(parent),
    m_dialog(new TransactionDialog(this)),
    m_menu(new QMenu(this)),
    m_addTransAction(new QAction("Add Transaction",m_menu))
{
    ui.setupUi(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    m_menu->addAction(m_addTransAction);
    connect(m_addTransAction,&QAction::triggered,m_dialog,[this](){m_dialog->createNew(m_account->Name());});
    connect(m_dialog,&TransactionDialog::NewTransaction, this,&AccountWidget::AddTransAction);
    connect(m_dialog,&TransactionDialog::ModifyTransaction,this,&AccountWidget::ModifyTransactions);
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
    connect(tmp,&TransactionWidget::ModifyTransaction,m_dialog,&TransactionDialog::modify);
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

