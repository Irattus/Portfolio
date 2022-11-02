#include "transactionwidget.h"

TransactionWidget::TransactionWidget(QWidget * parent)
    : QGroupBox(parent)
{
    setLayout(new QVBoxLayout(this));

    m_amountLabel = new QLabel(this);
    layout()->addWidget(m_amountLabel);
    layout()->addItem(new QSpacerItem(20,20));
    m_descriptionLabel = new QLabel(this);
    layout()->addWidget(m_descriptionLabel);
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
