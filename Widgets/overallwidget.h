#ifndef OVERALLWIDGET_H
#define OVERALLWIDGET_H
#include <QScrollArea>
#include "chartcontainer.h"
#include "Dialogs/accountdialog.h"
#include "Utilities/account.h"
#include "Utilities/bank.h"

class OverallWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit OverallWidget(QWidget *parent = nullptr);

    void setBank(std::shared_ptr<Bank> b);

    void addAccount(std::shared_ptr<Account> const& ac);
    void createAccount(std::shared_ptr<Account> const& ac);

    inline std::shared_ptr<Bank> bank() const { return m_bank; }

private slots:
private:
    QWidget * m_container;
    ChartContainer * m_chartContainer;

    std::shared_ptr<Bank> m_bank;

    QMenu * m_menu;
    QAction * m_addAccount;

    AccountDialog *  m_accountDialog;



};

#endif // OVERALLWIDGET_H
