#include "mw.h"
#define FILE "bank.dll"

MW::MW(QWidget *parent)
    : QMainWindow(parent),
      m_dialog(new AccountDialog(this))
{
    ui.setupUi(this);
    setWindowTitle("Portfolio");

    connect(m_dialog,&AccountDialog::NewAccount,this,
            [this](std::shared_ptr<Account> ac){
        m_bank->AddAccount( std::move(ac) );
        ui.yourMoney->AddAccount(m_bank->LastAccount());
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
    ui.yourMoney->Load(QString::fromUtf8(file.readAll()));
    file.close();
}

void MW::save()
{
    m_bank->OrderAccounts();
    std::cout<<(*m_bank.get());
    QFile file = QFile(FILE);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<(*m_bank.get());
    file.close();

}

MW::~MW()
{
    save();
}

void MW::on_actionRef_triggered()
{
    m_bank->Refs();
}

