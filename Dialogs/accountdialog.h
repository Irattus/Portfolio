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
    void ModifyAccount(QString &&);

private slots:
    void on_buttonBox_accepted();
signals:
    void NewAccount(std::shared_ptr<Account> const&);
    void ChangeAccount(QString);
private:
    Ui::AccountDialog ui;
    bool m_status;
};

#endif // ACCOUNTDIALOG_H
