#include "transactiondialog.h"

TransactionDialog::TransactionDialog(QWidget *parent) :
    QDialog(parent),
    m_status(false)
{
    ui.setupUi(this);
    ui.dateEdit->setDate(QDate::currentDate());
    ui.amoutDSP->setMaximum(std::numeric_limits<double>::max());
}

void TransactionDialog::on_buttonBox_accepted()
{
    m_transaction->changeDescription(ui.commentTextEdit->toPlainText());
    m_transaction->changeAmount(ui.amoutDSP->value() * (ui.costRadioButton->isChecked() ? -1 : 1));
    m_transaction->changeDate(ui.dateEdit->date());
    if(m_status)
        emit ModifyTransaction(m_transaction);
    else
        emit NewTransaction(m_transaction);
    m_transaction.reset();
}

void TransactionDialog::createNew(QString && name)
{
    setWindowTitle("Create Transaction");
    ui.AccountName->setText( name );
    ui.costRadioButton->setChecked(true);
    ui.commentTextEdit->setText("No description");
    ui.amoutDSP->setValue(15);
    m_transaction = std::make_shared<Transaction>(Transaction(QDate::currentDate(),0,""));
    show();
    m_status = false;
}

void TransactionDialog::modify(QString const& name,std::shared_ptr<Transaction> const& tr)
{
    setWindowTitle("Modify Transaction");
    ui.AccountName->setText(name);
    (tr->value() > 0 ? ui.entryRadioButton :ui.costRadioButton) ->setChecked(true);
    ui.amoutDSP->setValue( tr->value() * (tr->value() <0 ? -1 :1));
    ui.dateEdit->setDate(tr->date());
    ui.commentTextEdit->setText(tr->description());
    m_transaction = tr;
    show();
    m_status = true;
}

