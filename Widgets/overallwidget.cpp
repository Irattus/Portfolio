#include "overallwidget.h"
#include "accountwidget.h"
#include <QPushButton>

OverallWidget::OverallWidget(QWidget *parent) :
    QScrollArea(parent)
{
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    setWidgetResizable( true );
    m_container = new QWidget (this);
    m_container->setLayout(new QVBoxLayout(this));
    setWidget(m_container);

    m_accountDialog = new AccountDialog(this);
    m_menu = new QMenu(this);
    m_addAccount = new QAction("Add Account",m_menu);
    connect(m_addAccount,&QAction::triggered, m_accountDialog,&AccountDialog::createAccount);
    m_menu->addAction(m_addAccount);
    connect(m_accountDialog,&AccountDialog::newAccount, this,&OverallWidget::addAccount);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&OverallWidget::customContextMenuRequested,this,[this](QPoint const& pos){m_menu->exec(mapToGlobal(pos)); });

    m_pieChart = new ChartContainer(m_container);
    m_container->layout()->addWidget(m_pieChart);
    m_timeChart = new ChartContainer(m_container);
    m_container->layout()->addWidget(m_timeChart);

}

void OverallWidget::setBank(std::shared_ptr<Bank> bank)
{

    m_bank = m_pieChart->setBank(bank);
    Account ac;
    for(unsigned int i=0; i<m_bank->accounts();i++){
        createAccount(m_bank->getAccount(i));
        ac.appendTransaction(m_bank->getAccount(i)->allTransactions());
    }
    m_timeChart->setAccount(std::make_shared<Account>(ac));
}

void OverallWidget::addAccount(std::shared_ptr<Account> const& ac)
{
    m_bank->addAccount(ac);
    createAccount(ac);
}


void OverallWidget::createAccount(std::shared_ptr<Account> const& ac)
{
    AccountWidget * accountWidget = new AccountWidget(this);

    m_container->layout()->addWidget(accountWidget);

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
            m_container->layout()->removeWidget(accountWidget);
            accountWidget->deleteLater();
        }
    );
    accountMenu->addAction( m_addAccount );

    accountMenu->addAction( removeAccount );

    accountWidget->setMenu(accountMenu);

    accountWidget->setAccount( ac );
    accountWidget->reload();

    connect(accountWidget,&AccountWidget::reloadChart,m_pieChart,&ChartContainer::reload);
    connect(accountWidget,&AccountWidget::reloadChart,this,[this]()
    {
        Account ac;
        for(unsigned int i=0; i<m_bank->accounts();i++)
            ac.appendTransaction(m_bank->getAccount(i)->allTransactions());
        m_timeChart->setAccount(std::make_shared<Account>(ac));
    });

}

