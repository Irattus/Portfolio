#ifndef CHARTCONTAINER_H
#define CHARTCONTAINER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include "Utilities/bank.h"


class ChartContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ChartContainer(QWidget *parent = nullptr);
    inline std::shared_ptr<Bank> setBank(std::shared_ptr<Bank> bank) { m_bank = bank; reload(); return m_bank; }
    void reload();
private:
    unsigned int m_chartType;

    std::shared_ptr<Bank> m_bank;
    QChartView * m_chartView;
    QChart * m_pieChart;
    QChart * m_timeChart;

signals:

};

#endif // CHARTCONTAINER_H
