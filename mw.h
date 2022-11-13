#ifndef MW_H
#define MW_H
#include "Widgets/overallwidget.h"
#include "Dialogs/accountdialog.h"
#include"Utilities/bank.h"
#include <QFile>
#include <QMainWindow>
#include <QSettings>

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();

private slots:

private:
    OverallWidget * m_overAllWidget;
    std::shared_ptr<Bank> load();
    void save();
    std::shared_ptr<Bank> m_bank;
};
#endif // MW_H
