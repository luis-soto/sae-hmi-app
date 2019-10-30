#ifndef SYSTEMCONFIGURATION_H
#define SYSTEMCONFIGURATION_H

#include <QWidget>

namespace Ui {
class SystemConfiguration;
}

class SystemConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit SystemConfiguration(QWidget *parent = nullptr);
    ~SystemConfiguration();

private:
    Ui::SystemConfiguration *ui;
};

#endif // SYSTEMCONFIGURATION_H
