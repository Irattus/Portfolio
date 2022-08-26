#include "accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
}

void AccountDialog::CreateAccount()
{
    show();
    setWindowTitle("Create Account");
    ui.lineEdit->setText("New Account");
}

void AccountDialog::on_buttonBox_accepted()
{
    if(ui.lineEdit->text().isEmpty()) return;
    emit NewAccount(std::make_shared<Account>(Account(ui.lineEdit->text())));

}

