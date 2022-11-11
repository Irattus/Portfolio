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

enum ChartType{
    CT_PIE = 0,
    CT_TIME,
    CT_BOX
};

template<ChartType> class Charts;


class BaseChart : public QChart
{
public:
    BaseChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : QChart(parent,wFlags)
    {}

    virtual void setup(std::shared_ptr<Account>) = 0;
    virtual void setup(QVector<std::shared_ptr<Account>>) = 0;
};


template<> class Charts<CT_TIME> : public BaseChart
{
public:
    Charts<CT_TIME>(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : BaseChart(parent,wFlags)
    {
        legend()->hide();
    }
    void setup(std::shared_ptr<Account> ac);
private:
    inline void setup(QVector<std::shared_ptr<Account>>) {}


};


template<> class Charts<CT_PIE> : public BaseChart
{
public:
    Charts<CT_PIE>(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) : BaseChart(parent,wFlags)
    {}
    void setup(QVector<std::shared_ptr<Account>> listAcc);
private:
    inline void setup(std::shared_ptr<Account>) {}

};

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

class ChartContainer : public BaseChartContainer
{
public:
    explicit ChartContainer(QWidget *parent = nullptr) : BaseChartContainer(parent)  {}
    inline std::shared_ptr<Bank> setBank(std::shared_ptr<Bank> bank) { m_bank = bank; reload(); return m_bank; }
    inline std::shared_ptr<Account> setAccount(std::shared_ptr<Account> account)
    { m_account = account; reload(); return m_account; }

    void reload();
private:
    BaseChart * m_chart;
};

typedef Charts<CT_PIE> PieChart;
typedef Charts<CT_TIME> TimeChart;
typedef Charts<CT_BOX> BoxChart;

#endif // CHARTCONTAINER_H
