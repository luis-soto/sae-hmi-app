#include "base-plot.h"
#include "ui_base-plot.h"
#include "can-interface/can-interface.h"
#include <QDateTime>
//--------------------------------------------------------------------------------------------------
static const qint32 MAX_DATA_SIZE{1000};
//--------------------------------------------------------------------------------------------------
BasePlot::BasePlot(const QString& title, const qint32 id, QWidget* parent) : QWidget{parent},
    ui{new Ui::BasePlot}, _id{id}
{
    ui->setupUi(this);
    setTitle(title);

    ui->widPlot->addGraph();
    ui->widPlot->xAxis->setLabel(tr("time"));
    ui->widPlot->yAxis->setLabel(_title);

    CANInterface* can{CANInterface::getInstance()};
    connect(can, &CANInterface::newDataReceived, this, &BasePlot::newDataReceived, Qt::UniqueConnection);
}
//--------------------------------------------------------------------------------------------------
BasePlot::~BasePlot()
{
    delete ui;
}
//--------------------------------------------------------------------------------------------------
void BasePlot::setTitle(const QString &title)
{
    _title = title;
    ui->lblTitle->setText(title);
}
//--------------------------------------------------------------------------------------------------
qint32 BasePlot::getID() const
{
    return _id;
}
//--------------------------------------------------------------------------------------------------
const QString& BasePlot::getTitle() const
{
    return _title;
}
//--------------------------------------------------------------------------------------------------
void BasePlot::newDataReceived(const qint32 id, const qint32 data)
{
    static qreal counter{0};
    if(id == _id)
    {
        const qreal recData{static_cast<qreal>(data)/100};
        const qint32 dataSize{dataY.size()};

        if(dataSize >= MAX_DATA_SIZE)
        {
            dataX.pop_front();
            dataY.pop_front();
        }

        dataX.push_back(counter);
        counter = counter + 1;

        dataY.push_back(recData);

        ui->widPlot->graph(0)->setData(dataX, dataY);

        ui->widPlot->xAxis->setRange(dataX[0], dataX[0] + MAX_DATA_SIZE);
        ui->widPlot->yAxis->setRange(-10, 10);

        ui->leCurrentValue->setText(QString::number(recData));

        if(isVisible())
        {
            ui->widPlot->replot();
        }
    }
}
//--------------------------------------------------------------------------------------------------
