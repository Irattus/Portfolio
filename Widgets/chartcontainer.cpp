#include "chartcontainer.h"
#include <QPieSeries>
#include <QPushButton>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QLineSeries>

QLineSeries * getLineSeries(Account ac)
{

    double accountValue = 0;
    QLineSeries * Timeseries = new QLineSeries();
    for( unsigned int j = 0 ; j < ac.transactions(); j++){
        Transaction tempT = ac.getTransaction(j);
        QDateTime time = QDateTime::currentDateTime();
        time.setDate(tempT.m_time);
        accountValue += tempT.m_value;
        Timeseries->append(time.toSecsSinceEpoch(),accountValue);

    }
    return Timeseries;

}

ChartContainer::ChartContainer(QWidget *parent)
    : QWidget{parent}
{
    setLayout(new QVBoxLayout(this));
    setMinimumHeight(350);

    m_chartType = 0;

    m_pieChart = new QChart();
    m_timeChart = new QChart();

    m_chartView = new QChartView(this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    layout()->addWidget(m_chartView);
    QPushButton * push = new QPushButton(this);
    push->setText("Reload charts");
    connect(push,&QPushButton::clicked,this,&ChartContainer::reload);
    layout()->addWidget(push);
    QPushButton * pushT = new QPushButton(this);
    pushT->setText("Change charts");
    connect(pushT,&QPushButton::clicked,this,[this](){ m_chartType = m_chartType ? 0: 1; reload(); } );
    layout()->addWidget(pushT);

}

void ChartContainer::reload()
{
    m_pieChart->removeAllSeries();
    m_timeChart->removeAllSeries();
    QPieSlice * slice = new QPieSlice();
    QPieSeries * series = new QPieSeries();
    Account * ac = new Account();

    double max = 0;
    switch(m_chartType)
    {
        case 0:
            m_pieChart->addSeries(series);
            for( unsigned int i=0; i < m_bank->accounts(); ++i )
            {
                std::shared_ptr<Account> tmp = m_bank->getAccount(i);
                double n;
                if( (n = tmp->total()) ){
                    series->append(QString(tmp->name() + ": "+tmp->totalS()),n);
                    if( n > max)
                    {
                        max = n;
                        slice = series->slices().last();
                    }
                }

            }
            slice->setExploded();
            slice->setLabelVisible();

            m_chartView->setChart(m_pieChart);
        break;
        case 1:

            for( unsigned int i=0; i < m_bank->accounts(); ++i )
                ac->appendTransaction( m_bank->getAccount(i)->allTransactions() );
            ac->OrderTransactions();
            m_timeChart->legend()->hide();
            m_timeChart->addSeries(getLineSeries(*ac));
            QDateTimeAxis *axisX = new QDateTimeAxis;
            axisX->setTickCount(10);
            axisX->setFormat("yy.MM..dd");
            axisX->setTitleText("Date");

            m_timeChart->addAxis(axisX, Qt::AlignBottom);
            m_timeChart->series().last()->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis;
            axisY->setLabelFormat("%i");
            axisY->setMin(0);
            m_timeChart->addAxis(axisY, Qt::AlignLeft);
            m_timeChart->series().last()->attachAxis(axisY);

            m_chartView->setChart(m_timeChart);
        break;
    }


}

/*                double accountvalue=0;
                for( int j = 0 ; j < tmp->transactions(); j++){
                    Transaction tempT = tmp->getTransaction(j);
                    QDateTime time = QDateTime::currentDateTime();
                    time.setDate(tempT.m_time);
                    accountvalue += tempT.m_value;
                    Timeseries->append(time.toSecsSinceEpoch(),accountvalue);

                }
                m_timeChart->addSeries(Timeseries);
                QDateTimeAxis *axisX = new QDateTimeAxis;
                axisX->setTickCount(10);
                axisX->setFormat("yy.MM..dd");
                axisX->setTitleText("Date");

                m_timeChart->addAxis(axisX, Qt::AlignBottom);
                Timeseries->attachAxis(axisX);

                QValueAxis *axisY = new QValueAxis;
                axisY->setLabelFormat("%i");
                axisY->setTitleText(tmp->name());
                axisY->setMin(0);
                m_timeChart->addAxis(axisY, Qt::AlignLeft);
                Timeseries->attachAxis(axisY);*/
