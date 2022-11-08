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
    QChartView * m_chartView;


};




class TimeChart : public QChart
{
public:
    TimeChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : QChart(parent,wFlags)
    {
        legend()->hide();
    }

    inline void setup(Account ac)
    {
        ac.OrderTransactions();

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

    inline QLineSeries * getLineSeries(Account ac)
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

};

class PieChart : public QChart
{
public:
    PieChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : QChart(parent,wFlags)
    {

    }

    inline void setup(QVector<Account> listAcc)
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

    inline QPieSeries * getPieSeries(QVector<Account> listAcc)
    {
        QPieSeries * series = new QPieSeries;
        for( unsigned int i=0; i < listAcc.size(); ++i )
             series->append(QString(listAcc[i].name() + ": "+listAcc[i].totalS()),listAcc[i].total());
        return series;
     }


};

enum ChartType
{
    C_PIE,
    C_DATE,
};

template <typename T> class ChartContainer;

template<typename T>
class ChartContainer : public BaseChartContainer
{
public:
    explicit ChartContainer(QWidget *parent = nullptr) : BaseChartContainer(parent)  {}
    inline std::shared_ptr<Bank> setBank(std::shared_ptr<Bank> bank) { m_bank = bank; reload(); return m_bank; }

    inline void reload(){

    }
private:



};







#endif // CHARTCONTAINER_H
