#ifndef CANINTERFACE_H
#define CANINTERFACE_H

#include <QWidget>

class CANInterface : public QWidget
{
    Q_OBJECT
    public:
        static CANInterface* getInstance();

    private:
        explicit CANInterface(QWidget* parent = nullptr);
        ~CANInterface();

    signals:
        void newDataReceived(const qint32 id, const qint32 data);

    public slots:
};

#endif // CANINTERFACE_H
