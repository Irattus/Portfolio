#include "chartcontainer.h"
#include <QRandomGenerator64>
BaseChartContainer::BaseChartContainer(QWidget *parent)
    : QWidget{parent}
{
    setLayout(new QVBoxLayout(this));
    setMinimumHeight(350);

    m_chartView = new QChartView(this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    layout()->addWidget(m_chartView);

}

void TimeChart::setup(std::shared_ptr<Account> ac)
{
    ac->OrderTransactions();
    double accountValue = 0;
    QLineSeries * timeSeries = new QLineSeries;
    for( unsigned int j = 0 ; j < ac->transactions(); j++){
        timeSeries->append(
                    ac->getTransaction(j).m_time.toMSecsSinceEpoch()-1,
                    accountValue);
        timeSeries->append(
                    ac->getTransaction(j).m_time.toMSecsSinceEpoch(),
                    accountValue += ac->getTransaction(j).m_value);
    }
    addSeries(timeSeries);



    if(!timeSeries->count())
        return;
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(5);
    axisX->setFormat("dd.MM.yyyy");
    axisX->setTitleText("Date");
    axisX->setRange(ac->allTransactions().first().m_time,ac->allTransactions().last().m_time);

    addAxis(axisX, Qt::AlignBottom);
    timeSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");

    addAxis(axisY, Qt::AlignLeft);
    timeSeries->attachAxis(axisY);

}


void PieChart::setup(QVector<std::shared_ptr<Account>> listAcc)
{
    QPieSeries * pieSeries = new QPieSeries;
    for( unsigned int i=0; i < listAcc.size(); ++i )
        if(listAcc[i]->total()>0)
         pieSeries->append(QString(listAcc[i]->name() + ": "+listAcc[i]->totalS()),listAcc[i]->total());
    addSeries(pieSeries);

    if(!pieSeries->count())
        return;
    QPieSlice * slice = pieSeries->slices().at(0);
    slice->setExploded();
    slice->setLabelVisible();

}

std::shared_ptr<Bank> ChartContainer::setBank(std::shared_ptr<Bank> bank)
{
    m_bank = bank;
    if(m_bank->accounts())
        reload();
    return m_bank;
}

std::shared_ptr<Account> ChartContainer::setAccount(std::shared_ptr<Account> account)
{
    m_account = account;
    if(m_account->transactions())
        reload();
    return m_account;
}


void ChartContainer::reload(){
    if(m_bank){
        m_chart = new PieChart();
        m_chart->setup(m_bank->allAccounts());
    }
    if(m_account){
        m_chart = new TimeChart();
        m_chart->setup(m_account);

    }
    m_chart->setTheme((QChart::ChartTheme)QRandomGenerator::global()->bounded(7));
    m_chartView->setChart(m_chart);
}
