#include "accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    m_status(false)
{
    ui.setupUi(this);
}

void AccountDialog::CreateAccount()
{
    show();
    setWindowTitle("Create Account");
    ui.lineEdit->setText("New Account");
    m_status = true;
}

void AccountDialog::ModifyAccount(QString && name)
{
    show();
    setWindowTitle("Modify Account");
    ui.lineEdit->setText(name);
    m_status = false;
}

void AccountDialog::on_buttonBox_accepted()
{
    if(ui.lineEdit->text().isEmpty()) return;
    if(m_status)
        emit NewAccount(std::make_shared<Account>(Account(ui.lineEdit->text())));
    else
        emit ChangeAccount(ui.lineEdit->text());

}

