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
    m_status = true;
}

void AccountDialog::modifyAccount(QString const& name)
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
        emit newAccount(Account(ui.lineEdit->text()));
    else
        emit changeAccount(ui.lineEdit->text());

}

