#include "base-test-window.h"
#include "ui_base-test-window.h"
//--------------------------------------------------------------------------------------------------
BaseTestWindow::BaseTestWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainTestWindow)
{
    ui->setupUi(this);

    connect(ui->btnNextPage, &QPushButton::clicked, this, &BaseTestWindow::nextPage);
}
//--------------------------------------------------------------------------------------------------
BaseTestWindow::~BaseTestWindow()
{
    delete ui;
}
//--------------------------------------------------------------------------------------------------
void BaseTestWindow::setTitle(const QString& title)
{
    ui->lblTitle->setText(title);
}
//--------------------------------------------------------------------------------------------------
void BaseTestWindow::nextPage()
{
    qint32 newPage{ui->stackedWidget->currentIndex() + 1};

    (ui->stackedWidget->count() > newPage) ?
                 ui->stackedWidget->setCurrentIndex(newPage) : ui->stackedWidget->setCurrentIndex(0);
}
//--------------------------------------------------------------------------------------------------
