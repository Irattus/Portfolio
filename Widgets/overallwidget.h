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

    void setBank(std::shared_ptr<Bank> b);


    inline void AddAccount(Account &&ac)
    { m_accountContainer->addAccount(std::move(ac)); };
    inline void RemoveAccount(Account const& ac)
    { m_bank->removeAccount(ac); };

    inline std::shared_ptr<Bank> accounts() const { return m_bank; }

private:
    std::shared_ptr<Bank> m_bank;
    QScrollArea * m_scrollArea;
    AccountWidgetContainer * m_accountContainer;


};

#endif // OVERALLWIDGET_H
