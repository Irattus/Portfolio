#include "accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QGroupBox(parent),
    m_lazy(false)
{
    setLayout(new QVBoxLayout(this));
    m_transactionContainer = new QWidget(this);
    m_chart = new ChartContainer(this);
    layout()->addWidget(m_chart);
    layout()->addWidget(m_transactionContainer);
    m_transactionContainer->setLayout(new QVBoxLayout(m_transactionContainer));
    m_transactionContainer->layout()->setSpacing(1);



    connect(this,&AccountWidget::customContextMenuRequested, this, &AccountWidget::on_AccountWidget_customContextMenuRequested);

    m_transactionDialog = new TransactionDialog(this);
    connect(m_transactionDialog,&TransactionDialog::newTransaction,this,&AccountWidget::addTransactionWidget);
}

void AccountWidget::setMenu(QMenu * menu)
{
    menu->setTitle("Account");

    m_menu = new QMenu(this);

    QAction * addTransaction = new QAction("Add Transaction",m_menu);
    connect(addTransaction,&QAction::triggered,m_transactionDialog,
    [this]()
        {
            m_transactionDialog->createNew(m_account);
        }
    );
    m_menu->addAction(addTransaction);
    m_menu->addMenu(menu);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void AccountWidget::addTransactionWidget(Transaction const& tr)
{
    m_account->addTransaction(tr);
    createTransactionWidget(tr);
}

void AccountWidget::createTransactionWidget(Transaction const& tr)
{
    TransactionWidget * w = new TransactionWidget(m_transactionContainer);
    m_transactionContainer->layout()->addWidget(w);
    w->setValue(m_account,tr);
    w->setMenu(m_menu);
    QAction * modifyAction = new QAction("Modify Action", w);
    connect(modifyAction, &QAction::triggered,this,[this,tr](){m_transactionDialog->modifyTransaction(m_account,tr); });
    connect(w,&TransactionWidget::removeTransactionWidget,this,
    [this,w,tr]()
        {
            m_account->removeTransaction(tr);
            m_transactionContainer->layout()->removeWidget(w);
            w->deleteLater();
            reload();
        }
    );
    reload();
}

void AccountWidget::setAccount(std::shared_ptr<Account> const& a)
{
    m_account = a;
    m_lazy = true;
    m_chart->setAccount(m_account);
    for(unsigned int i=0; i < m_account->transactions(); i++)
        createTransactionWidget(m_account->getTransaction(i));
    m_lazy = false;
}

void AccountWidget::on_AccountWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menu->exec(mapToGlobal(pos),nullptr);
}

