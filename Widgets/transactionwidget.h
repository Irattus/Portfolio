#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include "ui_transactionwidget.h"
#include "Utilities/transaction.h"
#include <QMenu>

class TransactionWidget : public QFrame
{
    Q_OBJECT

public:
    explicit TransactionWidget(QWidget *parent = nullptr);
    void setTransaction(QString && name,std::shared_ptr<Transaction>&&);
    void setAddAction(QAction *);
    inline std::shared_ptr<Transaction> transaction() const { return m_transaction; };
public slots:
    void reload();
signals:
    void ModifyTransaction(QString const&, std::shared_ptr<Transaction> const& );
    void RemoveTransaction(TransactionWidget*);
public slots:
    void on_modifyButton_clicked();
    void on_deleteButton_clicked();

private slots:
    void on_TransactionWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::TransactionWidget ui;
    QString m_accountName;
    std::shared_ptr<Transaction> m_transaction;
    QMenu * m_menu;
    QAction * m_addTransAction;
    QAction * m_modifyTransAction;
    QAction * m_removeTransAction;
};

#endif // TRANSACTIONWIDGET_H
