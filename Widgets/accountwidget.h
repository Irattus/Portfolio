#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QGroupBox>
#include <QScrollArea>
#include <QList>
#include <QMenu>
#include <QAction>
#include "Utilities/account.h"
#include "transactionwidget.h"
#include "Dialogs/transactiondialog.h"
#include "chartcontainer.h"

class AccountWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr);
    void setMenu(QMenu * menu);
    void setAccount(std::shared_ptr<Account> const& a);
    void addTransactionWidget(Transaction const&tr);
    void createTransactionWidget(Transaction const&tr);



    inline std::shared_ptr<Account> account() const { return m_account; }

    inline void reload()
    {
      setTitle(m_account->name()+": "+m_account->totalS());
      m_chart->reload();
      emit reloadChart();
    }

private slots:
    void on_AccountWidget_customContextMenuRequested(const QPoint &pos);
private:
    std::shared_ptr<Account> m_account;
    ChartContainer * m_chart;
    QWidget * m_transactionContainer;
    QMenu * m_menu;
    TransactionDialog * m_transactionDialog;
    //QAction * m_modifyAccount;
signals:
    void reloadChart();
};

#endif // ACCOUNTWIDGET_H
