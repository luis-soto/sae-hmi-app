#include "pilot-view.h"
#include "ui_pilot-view.h"

PilotView::PilotView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PilotView)
{
    ui->setupUi(this);
}

PilotView::~PilotView()
{
    delete ui;
}
