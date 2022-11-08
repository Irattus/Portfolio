#include "accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    m_status(false)
{
    ui.setupUi(this);
}

void AccountDialog::createAccount()
{
    show();
    setWindowTitle("Create Account");
    ui.lineEdit->setText("New Account");
    ui.startingMoneySpinBox->setValue(0);
    m_status = true;
}

void AccountDialog::modifyAccount(QString const& name)
{
    show();
    setWindowTitle("Modify Account");
    ui.startMoneyLabel->setText("Change amount");
    ui.startingMoneySpinBox->setValue(0);
    ui.lineEdit->setText(name);
    m_status = false;
}

void AccountDialog::on_buttonBox_accepted()
{
    if(ui.lineEdit->text().isEmpty()) return;
    std::shared_ptr<Account> ac = std::make_shared<Account>(Account(ui.lineEdit->text()));
    ac->addTransaction({QDate::currentDate(),ui.startingMoneySpinBox->value(),"Starting Money"});
    if(m_status)
        emit newAccount(ac);
    else
        emit changeAccount(ui.lineEdit->text());

}

