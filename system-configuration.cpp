#include "system-configuration.h"
#include "ui_system-configuration.h"

SystemConfiguration::SystemConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemConfiguration)
{
    ui->setupUi(this);
}

SystemConfiguration::~SystemConfiguration()
{
    delete ui;
}
