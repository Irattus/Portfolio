#include "chartcontainer.h"

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
        Transaction tempT = ac->getTransaction(j);
        QDateTime time = QDateTime::currentDateTime();
        time.setDate(tempT.m_time);
        accountValue += tempT.m_value;
        timeSeries->append(time.toSecsSinceEpoch(),accountValue);

    }

    addSeries(timeSeries);


    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("yy.MM..dd");
    axisX->setTitleText("Date");

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
         pieSeries->append(QString(listAcc[i]->name() + ": "+listAcc[i]->totalS()),listAcc[i]->total());
    addSeries(pieSeries);

    if(!pieSeries->count())
        return;
    QPieSlice * slice = pieSeries->slices().at(0);
    slice->setExploded();
    slice->setLabelVisible();

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
    m_chartView->setChart(m_chart);
}
