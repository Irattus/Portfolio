#include "mw.h"
#define FILE "bank.dll"



MW::MW(QWidget *parent)
    : QMainWindow(parent),
      m_dialog(new AccountDialog(this))
{
    ui.setupUi(this);
    setWindowTitle("Portfolio");

    connect(m_dialog,&AccountDialog::newAccount,this,
            [this](Account ac){
        m_bank->addAccount( std::move(ac) );
        ui.yourMoney->AddAccount(m_bank->lastAccount());
    });

    connect(ui.actionNewAccount,&QAction::triggered,m_dialog,&AccountDialog::CreateAccount);
    ui.yourMoney->setBank(m_bank = load());

}

std::shared_ptr<Bank> MW::load()
{
    QFile file = QFile(FILE);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    Bank b;
    in>>b;
    file.close();
    return std::make_shared<Bank>(b);
}

void MW::save()
{
    m_bank->OrderAccounts();
    Bank b = *m_bank.get();
    QFile file = QFile(FILE);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<b;
    file.close();

}

MW::~MW()
{
    save();
}

