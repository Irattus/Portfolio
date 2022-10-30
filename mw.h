#ifndef MW_H
#define MW_H

#include "ui_mw.h"
#include "Widgets/overallwidget.h"
#include "Dialogs/accountdialog.h"
#include"Utilities/bank.h"
#include <QFile>
#include <QMainWindow>

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();

private slots:
    void on_actionRef_triggered();

private:
    Ui::MW ui;
    void load();
    void save();
    std::shared_ptr<Bank> m_bank;
    AccountDialog * m_dialog;
};
#endif // MW_H