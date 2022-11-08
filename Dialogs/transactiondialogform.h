#ifndef TRANSACTIONDIALOGFORM_H
#define TRANSACTIONDIALOGFORM_H

#include <QWidget>

namespace Ui {
class TransactionDialogForm;
}

class TransactionDialogForm : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionDialogForm(QWidget *parent = nullptr);
    ~TransactionDialogForm();

private:
    Ui::TransactionDialogForm *ui;
};

#endif // TRANSACTIONDIALOGFORM_H
