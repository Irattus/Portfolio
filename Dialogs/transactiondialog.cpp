#include "transactiondialog.h"

TransactionDialog::TransactionDialog(QWidget *parent) :
    QDialog(parent),
    m_status(false)
{
    ui.setupUi(this);
    ui.calendarWidget->setCurrentPage(QDate::currentDate().year(),QDate::currentDate().month());
    ui.amoutDSP->setMaximum(std::numeric_limits<double>::max());
}

void TransactionDialog::on_buttonBox_accepted()
{
    Transaction transaction;
    transaction.m_description = ui.commentTextEdit->toPlainText();
    transaction.m_value = (ui.amoutDSP->value() * (ui.costRadioButton->isChecked() ? -1 : 1));
    transaction.m_time = QDateTime::currentDateTime();
    transaction.m_time.setDate(ui.calendarWidget->selectedDate());
    if(m_status)
        emit modifyTransaction(m_account,transaction);
    else
        emit newTransaction(transaction);
}

void TransactionDialog::createNew(std::shared_ptr<Account> const&  ac)
{
    m_account = ac;
    setWindowTitle("Create Transaction");
    ui.AccountName->setText( ac->name() );
    ui.costRadioButton->setChecked(true);
    ui.commentTextEdit->setText("No description");
    ui.amoutDSP->setValue(15);
    show();
    m_status = false;
}

void TransactionDialog::modify(std::shared_ptr<Account> const&  ac,Transaction const& tr)
{
    m_account = ac;
    setWindowTitle("Modify Transaction");
    ui.AccountName->setText(ac->name());
    (tr.m_value > 0 ? ui.entryRadioButton :ui.costRadioButton) ->setChecked(true);
    ui.amoutDSP->setValue( tr.m_value * (tr.m_value <0 ? -1 :1));
    ui.calendarWidget->setCurrentPage(tr.m_time.date().year(),tr.m_time.date().month());
    ui.commentTextEdit->setText(tr.m_description);
    show();
    m_status = true;
}

