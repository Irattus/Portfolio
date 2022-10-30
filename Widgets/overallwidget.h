#ifndef OVERALLWIDGET_H
#define OVERALLWIDGET_H
#include <QScrollArea>
#include "Widgets/accountwidgetcontainer.h"
#include "Utilities/account.h"
#include "Utilities/bank.h"

class OverallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverallWidget(QWidget *parent = nullptr);

    inline void setBank(std::shared_ptr<Bank> b) { m_bank = b; }

    void Load(QString && text);

    inline void AddAccount(std::shared_ptr<Account> &&ac)
    { m_accountContainer->AddAccount(std::move(ac)); };
    inline void RemoveAccount(std::shared_ptr<Account> const& ac)
    { m_bank->RemoveAccount(ac); };

    inline std::shared_ptr<Bank> accounts() const { return m_bank; }

private:
    std::shared_ptr<Bank> m_bank;
    QScrollArea * m_scrollArea;
    AccountWidgetContainer * m_accountContainer;


};

#endif // OVERALLWIDGET_H
