#include "mw.h"
#define FILE "bank.dll"

MW::MW(QWidget *parent)
    : QMainWindow(parent),
      m_dialog(new AccountDialog(this))
{
    ui.setupUi(this);
    setWindowTitle("Portfolio");

    connect(m_dialog,&AccountDialog::NewAccount,this,
            [this](Account ac){
        m_bank->addAccount( std::move(ac) );
        ui.yourMoney->AddAccount(m_bank->lastAccount());
    });

    connect(ui.actionNewAccount,&QAction::triggered,m_dialog,&AccountDialog::CreateAccount);

    m_bank = std::make_shared<Bank>(Bank());
    ui.yourMoney->setBank(m_bank);
    load();
}

void MW::load()
{
    QFile file = QFile(FILE);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in>>*m_bank.get();
    file.close();
}

void MW::save()
{
    m_bank->OrderAccounts();
    QFile file = QFile(FILE);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<(m_bank.get());
    file.close();

}

MW::~MW()
{
    save();
}

