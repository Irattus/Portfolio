#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include "ui_accountdialog.h"
#include "Utilities/account.h"


class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = nullptr);
    void createAccount();
    void modifyAccount(QString const&);
signals:
    void newAccount(std::shared_ptr<Account> const&);
    void changeAccount(QString);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AccountDialog ui;
    bool m_status;
};

#endif // ACCOUNTDIALOG_H
