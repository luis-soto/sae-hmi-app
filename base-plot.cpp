#include "base-plot.h"
#include "ui_base-plot.h"
#include "can-interface/can-interface.h"
#include <QDateTime>
#include <algorithm>
//--------------------------------------------------------------------------------------------------
static const qint32 MAX_DATA_SIZE{1000};
//--------------------------------------------------------------------------------------------------
BasePlot::BasePlot(const QString& title, const qint32 id, QWidget* parent) : QWidget{parent},
    _ui{new Ui::BasePlot}, _id{id}
{
    _ui->setupUi(this);
    setTitle(title);

    _ui->widPlot->addGraph();
    _ui->widPlot->xAxis->setLabel(tr("time"));
    _ui->widPlot->yAxis->setLabel(_title);

    CANInterface* can{CANInterface::getInstance()};
    connect(can, &CANInterface::newDataReceived, this, &BasePlot::newDataReceived, Qt::UniqueConnection);
}
//--------------------------------------------------------------------------------------------------
BasePlot::~BasePlot()
{
    delete _ui;
}
//--------------------------------------------------------------------------------------------------
void BasePlot::setTitle(const QString &title)
{
    _title = title;
    _ui->lblTitle->setText(title);
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
qreal BasePlot::findMinimum(const QVector<qreal>& data)
{
    return *std::min_element(data.constBegin(), data.constEnd());
}
//--------------------------------------------------------------------------------------------------
qreal BasePlot::findMaximum(const QVector<qreal> &data)
{
    return *std::max_element(data.constBegin(), data.constEnd());
}
//--------------------------------------------------------------------------------------------------
void BasePlot::newDataReceived(const qint32 id, const qint32 data)
{
    static qreal startTime{static_cast<qreal>(QDateTime::currentMSecsSinceEpoch())};

    if(id == _id)
    {
        const qreal recData{static_cast<qreal>(data)/_propConst};
        const qreal time{static_cast<qreal>(QDateTime::currentMSecsSinceEpoch()) - startTime};

        if(_dataY.size() >= MAX_DATA_SIZE)
        {
            _dataX.pop_front();
            _dataY.pop_front();
        }

        _dataX.push_back(time);
        _dataY.push_back(recData);

        updatePlot();
    }
}
//--------------------------------------------------------------------------------------------------
void BasePlot::updatePlot()
{
    if(isVisible() && !_dataY.empty())
    {
        _ui->widPlot->graph(0)->setData(_dataX, _dataY);

        _ui->widPlot->xAxis->setRange(findMinimum(_dataX), findMaximum(_dataX));
        _ui->widPlot->yAxis->setRange(findMinimum(_dataY), findMaximum(_dataY));

        _ui->leCurrentValue->setText(QString::number(_dataY.last()));

        _ui->widPlot->replot();
    }
}
//--------------------------------------------------------------------------------------------------
