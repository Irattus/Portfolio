#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include "ui_accountdialog.h"
#include "Utilities/account.h"


class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = nullptr);
    void CreateAccount();
    void ModifyAccount();

private slots:
    void on_buttonBox_accepted();
signals:
    void NewAccount(std::shared_ptr<Account> const&);

private:
    Ui::AccountDialog ui;
};

#endif // ACCOUNTDIALOG_H
