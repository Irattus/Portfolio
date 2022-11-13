#include "mw.h"
#define FILE "bank.dll"



MW::MW(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Your Money");
    m_overAllWidget= new OverallWidget(this);
    setCentralWidget(m_overAllWidget);
    m_overAllWidget->setBank(m_bank = load());
    setMinimumSize(QSize(600,400));




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
    QFile file = QFile(FILE);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<m_bank;
    file.close();

}

MW::~MW()
{
    save();
}

