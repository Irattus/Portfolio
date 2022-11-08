#ifndef CHARTCONTAINER_H
#define CHARTCONTAINER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QPieSeries>
#include <QPushButton>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QLineSeries>
#include "Utilities/bank.h"


class BaseChartContainer : public QWidget
{
    Q_OBJECT
public:
    explicit BaseChartContainer(QWidget *parent = nullptr);

    virtual void reload() = 0;
protected:

    std::shared_ptr<Bank> m_bank;
    std::shared_ptr<Account> m_account;
    QChartView * m_chartView;


};

class BaseChart : public QChart
{
public:
    BaseChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : QChart(parent,wFlags)
    {

    }

    virtual void setup(std::shared_ptr<Account>) = 0;
    virtual void setup(QVector<std::shared_ptr<Account>>) = 0;
};


class TimeChart : public BaseChart
{
public:
    TimeChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : BaseChart(parent,wFlags)
    {
        legend()->hide();
    }

    inline void setup(QVector<std::shared_ptr<Account>>) {}
    inline void setup(std::shared_ptr<Account> ac)
    {
        ac->OrderTransactions();

        QLineSeries * timeSeries = getLineSeries(ac);
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
private:

    inline QLineSeries * getLineSeries(std::shared_ptr<Account> ac)
    {

        double accountValue = 0;
        QLineSeries * Timeseries = new QLineSeries();
        for( unsigned int j = 0 ; j < ac->transactions(); j++){
            Transaction tempT = ac->getTransaction(j);
            QDateTime time = QDateTime::currentDateTime();
            time.setDate(tempT.m_time);
            accountValue += tempT.m_value;
            Timeseries->append(time.toSecsSinceEpoch(),accountValue);

        }
        return Timeseries;

    }

};

class PieChart : public BaseChart
{
public:
    PieChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : BaseChart(parent,wFlags)
    {

    }
    inline void setup(std::shared_ptr<Account>) {}
    inline void setup(QVector<std::shared_ptr<Account>> listAcc)
    {
        QPieSeries * pieSeries = getPieSeries(listAcc);
        addSeries(pieSeries);

        if(!pieSeries->count())
            return;
        QPieSlice * slice = pieSeries->slices().at(0);
        slice->setExploded();
        slice->setLabelVisible();

    }
private:

    inline QPieSeries * getPieSeries(QVector<std::shared_ptr<Account>> listAcc)
    {
        QPieSeries * series = new QPieSeries;
        for( unsigned int i=0; i < listAcc.size(); ++i )
             series->append(QString(listAcc[i]->name() + ": "+listAcc[i]->totalS()),listAcc[i]->total());
        return series;
     }


};

class ChartContainer : public BaseChartContainer
{
public:
    explicit ChartContainer(QWidget *parent = nullptr) : BaseChartContainer(parent)  {}
    inline std::shared_ptr<Bank> setBank(std::shared_ptr<Bank> bank) { m_bank = bank; reload(); return m_bank; }
    inline std::shared_ptr<Account> setAccount(std::shared_ptr<Account> account)
    { m_account = account; reload(); return m_account; }

    inline void reload(){
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
private:
    BaseChart * m_chart;



};

#endif // CHARTCONTAINER_H
