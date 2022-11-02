#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include "ui_transactionwidget.h"
#include "Utilities/account.h"
#include <QMenu>

class TransactionWidget : public QFrame
{
    Q_OBJECT

public:
    explicit TransactionWidget(QWidget *parent = nullptr);
    void setTransaction(QString && name,Transaction &&);
    void setAddAction(QAction *);
    inline Transaction transaction() const { return m_transaction; };
public slots:
    void reload();
signals:
    void modifyTransaction(QString const&, Transaction const& );
    void removeTransaction(TransactionWidget*);
public slots:
    void on_modifyButton_clicked();
    void on_deleteButton_clicked();

private slots:
    void on_TransactionWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::TransactionWidget ui;
    std::shared_ptr<Account> m_account;
    Transaction m_transaction;
    QMenu * m_transactionMenu;
};

#endif // TRANSACTIONWIDGET_H
