#include "chartwidgetcontainer.h"
#include "ui_chartwidgetcontainer.h"

ChartWidgetContainer::ChartWidgetContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidgetContainer)
{
    ui->setupUi(this);
}

ChartWidgetContainer::~ChartWidgetContainer()
{
    delete ui;
}
