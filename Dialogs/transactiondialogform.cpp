#include "transactiondialogform.h"
#include "ui_transactiondialogform.h"

TransactionDialogForm::TransactionDialogForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionDialogForm)
{
    ui->setupUi(this);
}

TransactionDialogForm::~TransactionDialogForm()
{
    delete ui;
}
