#ifndef OVERALLWIDGET_H
#define OVERALLWIDGET_H
#include "Utilities/account.h"
#include "ui_overallwidget.h"
#include "Utilities/bank.h"

class OverallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverallWidget(QWidget *parent = nullptr);

    inline void setBank(std::shared_ptr<Bank> b) { m_bank = b; }

    void Load(QString && text);

    inline void AddAccount(std::shared_ptr<Account> &&ac)
    { ui.container->AddAccount(std::move(ac)); };
    inline void RemoveAccount(std::shared_ptr<Account> const& ac)
    { m_bank->RemoveAccount(ac); };

    inline std::shared_ptr<Bank> accounts() const { return m_bank; }

private:
    Ui::OverallWidget ui;
    std::shared_ptr<Bank> m_bank;

};

#endif // OVERALLWIDGET_H
