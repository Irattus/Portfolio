#include "transactionwidget.h"

TransactionWidget::TransactionWidget(QWidget *parent) :
    QFrame(parent),
    m_menu(new QMenu(this)),
    m_modifyTransAction(new QAction("Modify Transaction",m_menu)),
    m_removeTransAction(new QAction("Remove Transaction",m_menu))
{
    ui.setupUi(this);
}

void TransactionWidget::setAddAction(QAction * ac)
{
    m_addTransAction = ac;
    setContextMenuPolicy(Qt::CustomContextMenu);
    m_menu->addAction(m_addTransAction);
    m_menu->addAction(m_modifyTransAction);
    m_menu->addAction(m_removeTransAction);
    connect(m_modifyTransAction,&QAction::triggered,this,&TransactionWidget::on_modifyButton_clicked);
    connect(m_removeTransAction,&QAction::triggered,this,&TransactionWidget::on_deleteButton_clicked);
}


void TransactionWidget::setTransaction(QString && name,Transaction&& tr)
{
    m_accountName = std::move(name);
    m_transaction = std::move(tr);
    reload();
}

void TransactionWidget::reload()
{
    ui.description->setText(m_transaction.m_description);
    ui.date->setText(m_transaction.m_time.toString("dd.MM.yyyy"));
    ui.amount->setStyleSheet(
                m_transaction.m_value > 0 ?
                  "color: green" : "color: red" );
    ui.amount->setFont(QFont("Cambria",12,QFont::Bold));
    ui.amount->setText(QString::number(m_transaction.m_value,'f',2));
}

void TransactionWidget::on_modifyButton_clicked()
{
    emit modifyTransaction(m_accountName,m_transaction);
}


void TransactionWidget::on_deleteButton_clicked()
{
    emit removeTransaction(this);
}


void TransactionWidget::on_TransactionWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menu->exec(mapToGlobal(pos),nullptr);
}

