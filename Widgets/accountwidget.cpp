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

void AccountWidget::setMenu(QMenu * menu)
{
    m_menu = menu;
    QAction * addTransaction = new QAction("Add Transaction",m_menu);
    /*connect(addTransaction,&QAction::triggered,m_dial,
    [this]()
        {
            m_transactionDialog->createNew(m_account);
        }
    );*/
    m_menu->addAction(addTransaction);

}

void AccountWidget::addTransActionWidget(Transaction const& tr)
{
    reload();
}

void AccountWidget::setAccount(std::shared_ptr<Account> const& a)
{
    m_account = a;
    for(unsigned int i=0; i < m_account->transactions(); i++)
        addTransActionWidget(m_account->getTransaction(i));
}

void AccountWidget::on_AccountWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menu->exec(mapToGlobal(pos),nullptr);
}

