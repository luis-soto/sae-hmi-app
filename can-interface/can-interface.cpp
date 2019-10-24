#include "can-interface.h"
#include <QTimer>
//--------------------------------------------------------------------------------------------------
static CANInterface* inst{nullptr};
//--------------------------------------------------------------------------------------------------
CANInterface* CANInterface::getInstance()
{
    if(nullptr == inst)
    {
        inst = new CANInterface;
    }

    inst->createGenerator();

    return inst;
}
//--------------------------------------------------------------------------------------------------
CANInterface::CANInterface(QWidget* parent) : QWidget(parent)
{
}
//--------------------------------------------------------------------------------------------------
CANInterface::~CANInterface()
{

}
//--------------------------------------------------------------------------------------------------
void CANInterface::createGenerator()
{
    static qint32 maxIdx{0};
    _dataGenerator = new QTimer(this);

    connect(_dataGenerator, &QTimer::timeout, this, [=]()
    {
        static qint32 data{0};
        static qint32 limit{1000};
        static qint32 idx{0};

        idx++;

        bool exceed{false};

        if(limit > 0)
        {
            data = data + 2;
            exceed = (limit <= data);
        }
        else
        {
            data = data - 2;
            exceed = (limit >= data);
        }

        if(exceed)
        {
            limit = -1*limit;
        }

        if(idx > maxIdx)
        {
            idx = 1;
        }

        emit newDataReceived(idx, data);

    });

    maxIdx++;

    _dataGenerator->start(1);
}
//--------------------------------------------------------------------------------------------------
