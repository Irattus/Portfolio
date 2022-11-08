#include "transactionwidget.h"

TransactionWidget::TransactionWidget(QWidget * parent)
    : QGroupBox(parent)
{
    setLayout(new QVBoxLayout(this));

    m_amountLabel = new QLabel(this);
    layout()->addWidget(m_amountLabel);
    layout()->addItem(new QSpacerItem(10,10));
    m_descriptionLabel = new QLabel(this);
    layout()->addWidget(m_descriptionLabel);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,&TransactionWidget::customContextMenuRequested,this,[this](QPoint const& pos) { m_menu->exec(mapToGlobal(pos),nullptr); });
}

void TransactionWidget::setValue(std::shared_ptr<Account> const& ac,Transaction const& tr)
{
    m_account = ac;
    setTitle(tr.m_time.toString("dd.MM.yy"));
    setFont(QFont("Cambria",14,QFont::Normal));
    m_amountLabel->setStyleSheet(tr.m_value > 0 ? "color:green" : "color:red");
    m_amountLabel->setText(QString::number(tr.m_value,'f',2));
    m_amountLabel->setFont(QFont("Cambria",14,QFont::Bold));
    m_descriptionLabel->setText(tr.m_description);
    m_descriptionLabel->setFont(QFont("Cambria",10,QFont::Normal));
}

void TransactionWidget::setMenu(QMenu * menu)
{
    m_menu = new QMenu(this);
    m_menu->addAction(menu->actions().at(0));
    QAction * removeTransaction = new QAction("Remove Transaction",menu);
    connect(removeTransaction,&QAction::triggered,this,&TransactionWidget::removeTransactionWidget);
    m_menu->addAction(removeTransaction);
    m_menu->addMenu(menu->actions().at(1)->menu());
}
