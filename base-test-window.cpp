#include "base-test-window.h"
#include "ui_base-test-window.h"
#include "base-plot.h"
#include <QDebug>
//--------------------------------------------------------------------------------------------------
static const qint32 SIZE{2};
static const qint32 ITEMS_BY_PAGE{SIZE*SIZE};
//--------------------------------------------------------------------------------------------------
BaseTestWindow::BaseTestWindow(QWidget* parent, const QString& title):
                                                        QWidget{parent}, ui{new Ui::MainTestWindow}
{
    ui->setupUi(this);
    setTitle(title);
    ui->btnNextPage->setVisible(false);
}
//--------------------------------------------------------------------------------------------------
BaseTestWindow::~BaseTestWindow()
{
    delete ui;
}
//--------------------------------------------------------------------------------------------------
void BaseTestWindow::addPlot(const QString& title, const qint32 id)
{
    BasePlot* newPlot{new BasePlot(title, id, this)};

    _plots.push_back(newPlot);

    connect(this, &BaseTestWindow::visibilityChanged, newPlot, &BasePlot::updatePlot);
}
//--------------------------------------------------------------------------------------------------
void BaseTestWindow::setTitle(const QString& title)
{
    ui->lblTitle->setText(title);
}
//--------------------------------------------------------------------------------------------------
void BaseTestWindow::mountView()
{
    qint32 pageIdx{0};
    qint32 idx{0};

    QGridLayout* layout{nullptr};

    for(QWidget* const basePlot : _plots)
    {
        if(ITEMS_BY_PAGE <= pageIdx)
        {
            pageIdx = 0;
            layout = nullptr;
        }

        if(nullptr == layout)
        {
            QWidget* wid{new QWidget(ui->stackedWidget)};
            layout = new QGridLayout(wid);
            wid->setLayout(layout);
            ui->stackedWidget->addWidget(wid);
        }

        qint32 rowSpan{1};
        qint32 colSpan{1};
        qint32 x{pageIdx/SIZE};
        qint32 y{pageIdx%SIZE};


        if(_plots.size() == idx+1)
        {
            if(layout->count() == 2)
            {
                colSpan++;
            }

            if(layout->count() == 1)
            {
                x = 1;
                y = 0;
            }
        }

        layout->addWidget(basePlot, x, y, rowSpan, colSpan);

        idx++;
        pageIdx++;
    }

    ui->btnNextPage->setVisible(ui->stackedWidget->count() > 1);
}
//--------------------------------------------------------------------------------------------------
void BaseTestWindow::on_btnNextPage_clicked()
{
    const qint32 numberOfPages{ui->stackedWidget->count()};

    if(numberOfPages > 1)
    {
        const qint32 newPage{ui->stackedWidget->currentIndex() + 1};

        (numberOfPages > newPage) ?
                     ui->stackedWidget->setCurrentIndex(newPage) : ui->stackedWidget->setCurrentIndex(0);
    }
}
//--------------------------------------------------------------------------------------------------
