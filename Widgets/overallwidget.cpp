#include "overallwidget.h"
#include "accountwidget.h"

OverallWidget::OverallWidget(QWidget *parent) :
    QScrollArea(parent)
{
    setLayout(new QVBoxLayout(this));
    m_accountDialog = new AccountDialog(this);
    m_menu = new QMenu(this);
    m_addAccount = new QAction("Add Account",m_menu);
    connect(m_addAccount,&QAction::triggered, m_accountDialog,&AccountDialog::createAccount);
    m_menu->addAction(m_addAccount);
    connect(m_accountDialog,&AccountDialog::newAccount, this,&OverallWidget::addAccount);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&OverallWidget::customContextMenuRequested,this,[this](QPoint const& pos){m_menu->exec(mapToGlobal(pos)); });
}

void OverallWidget::setBank(std::shared_ptr<Bank> bank)
{
    m_bank = bank;
    for(unsigned int i=0; i<m_bank->accounts();i++)
        createAccount(m_bank->getAccount(i));

}

void OverallWidget::addAccount(std::shared_ptr<Account> const& ac)
{
    m_bank->addAccount(ac);
    createAccount(ac);
}


void OverallWidget::createAccount(std::shared_ptr<Account> const& ac)
{
    AccountWidget * accountWidget = new AccountWidget(this);
    accountWidget->setAccount( ac );
    accountWidget->reload();
    layout()->addWidget(accountWidget);

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
            layout()->removeWidget(accountWidget);
            accountWidget->deleteLater();
        }
    );
    accountMenu->addAction( m_addAccount );

    accountMenu->addAction( removeAccount );

    accountWidget->setMenu(accountMenu);

}

