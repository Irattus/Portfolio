#include "overallwidget.h"
#include "accountwidget.h"

OverallWidget::OverallWidget(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    m_scrollArea = new QScrollArea;
    m_accountContainer = new WidgetContainer(m_scrollArea);
    layout()->addWidget(m_scrollArea);
    m_scrollArea->setWidget(m_accountContainer);
    m_accountDialog = new AccountDialog(this);
    m_transactionDialog = new TransactionDialog(this);



}

void OverallWidget::setBank(std::shared_ptr<Bank> bank)
{
    m_bank = bank;
    for (unsigned int i=0; i< m_bank->accounts(); i++)
        addAccount(m_bank->getAccount(i));
}


void OverallWidget::addAccount(Account const& ac)
{

    AccountWidget * accountWidget = new AccountWidget(this);

    QMenu * accountMenu = new QMenu(accountWidget);

    /*QAction * modifyAccount = new QAction("Modify Account",tmp);
    connect(modifyAccount,&QAction::triggered,tmp,
    [this,ac]()
        {
            m_accountDialog->modifyAccount(ac.name());
        }
    );*/

    QAction * removeAccount = new QAction("Remove Account",accountMenu);
    connect(removeAccount,&QAction::triggered,this,
    [this,accountWidget,ac]()
        {
            m_bank->removeAccount(ac);
            m_accountContainer->removeWidget(accountWidget);
            accountWidget->deleteLater();
        }
    );

    QAction * addTransaction = new QAction("Add Transaction",accountMenu);
    connect(addTransaction,&QAction::triggered,m_transactionDialog,
    [this,ac]()
        {
            m_transactionDialog->createNew(ac);
        }
    );

    //Transaction Dialog

    connect(m_transactionDialog,&TransactionDialog::modifyTransaction,this,
    [](Account const& ac,Transaction const& tr)
        {
            //modify
        }
    );

    connect(m_transactionDialog,&TransactionDialog::newTransaction,this,
    [this](Account const& ac,Transaction const& tr)
        {
            m_bank->addTransaction(ac,tr);
        }
    );

    //Transaction Widget Menu

    QMenu * transactionMenu = new QMenu(this);

    QAction * modifyTransaction = new QAction("Modify Transaction",transactionMenu);
    connect(modifyTransaction,&QAction::triggered,this,
    []()
        {
            //modify
        }
    );

    QAction * removeTransaction = new QAction("Remove Transaction",transactionMenu);
    connect(removeTransaction,&QAction::triggered,this,
    []()
        {
            //remove
        }
    );



    transactionMenu->addAction(addTransaction);
    transactionMenu->addAction(modifyTransaction);
    transactionMenu->addAction(removeTransaction);

    accountMenu->addAction( addTransaction );
    accountMenu->addAction( removeAccount );

    accountWidget->setMenu(accountMenu);
    accountWidget->setAccount( ac );
    accountWidget->reload();
    m_accountContainer->addWidget(accountWidget);
}

