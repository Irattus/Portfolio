#ifndef OVERALLWIDGET_H
#define OVERALLWIDGET_H
#include <QScrollArea>
#include "Widgets/widgetcontainer.h"
#include "Dialogs/accountdialog.h"
#include "Dialogs/transactiondialog.h"
#include "Utilities/account.h"
#include "Utilities/bank.h"

class OverallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverallWidget(QWidget *parent = nullptr);

    void setBank(std::shared_ptr<Bank> b);

    void addAccount(Account const& ac);

    inline std::shared_ptr<Bank> bank() const { return m_bank; }

private:
    std::shared_ptr<Bank> m_bank;
    QScrollArea * m_scrollArea;
    WidgetContainer * m_accountContainer;
    AccountDialog *  m_accountDialog;
    TransactionDialog * m_transactionDialog;



};

#endif // OVERALLWIDGET_H
