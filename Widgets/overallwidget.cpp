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
    m_menu = new QMenu(this);
    QAction * addAccountAction = new QAction("Add Account",m_menu);
    connect(addAccountAction,&QAction::triggered, m_accountDialog,&AccountDialog::createAccount);
    m_menu->addAction(addAccountAction);
    connect(m_accountDialog,&AccountDialog::newAccount, this,&OverallWidget::addAccount);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&OverallWidget::customContextMenuRequested,this,[this](QPoint const& pos){m_menu->exec(mapToGlobal(pos)); });
}

void OverallWidget::setBank(std::shared_ptr<Bank> bank)
{
    m_bank = bank;
    for(int i=0; i<m_bank->accounts();i++)
        createAccount(m_bank->getAccount(i));

}

void OverallWidget::addAccount(std::shared_ptr<Account> const& ac)
{
    m_bank->addAccount(ac);
    createAccount(ac);
}


void OverallWidget::createAccount(std::shared_ptr<Account> const& ac)
{
    AccountWidget * accountWidget = new AccountWidget(m_accountContainer);
    accountWidget->setAccount( ac );
    accountWidget->reload();
    m_accountContainer->addWidget(accountWidget);

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




/*  ui.amount->setStyleSheet(
                m_transaction.m_value > 0 ?
                  "color: green" : "color: red" );
    ui.amount->setFont(QFont("Cambria",12,QFont::Bold));*/

    accountMenu->addAction( removeAccount );

    accountWidget->setMenu(accountMenu);

}

