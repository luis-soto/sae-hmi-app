#include <QPixmap>

#include <QDebug>
//--------------------------------------------------------------------------------------------------
#include "main-sae-hmi-app.h"
#include "ui_main-sae-hmi-app.h"
#include "base-test-window.h"
//--------------------------------------------------------------------------------------------------
MainSAEHMIApp::MainSAEHMIApp(QWidget *parent): QWidget(parent), ui(new Ui::MainSAEHMIApp)
{
    ui->setupUi(this);

    ui->btnPilotView->setIcon(QPixmap{":/icons/icons/pilot-view-icon.png"});
    ui->btnBackTest->setIcon(QPixmap{":/icons/icons/back-test-icon.png"});
    ui->btnCommTest->setIcon(QPixmap{":/icons/icons/comm-test-icon.png"});
    ui->btnFrontTest->setIcon(QPixmap{":/icons/icons/front-test-icon.png"});
    ui->btnTurboTest->setIcon(QPixmap{":/icons/icons/turbo-test-icon.png"});
    ui->btnInjectionTest->setIcon(QPixmap{":/icons/icons/injection-test-icon.png"});

    createWindows();

    connect(ui->btnPilotView, &QToolButton::clicked, this, &MainSAEHMIApp::onbtnPilotView_clicked);
    connect(ui->btnFrontTest, &QToolButton::clicked, this, &MainSAEHMIApp::onbtnFrontTest_clicked);
    connect(ui->btnTurboTest, &QToolButton::clicked, this, &MainSAEHMIApp::onbtnTurboTest_clicked);
    connect(ui->btnInjectionTest, &QToolButton::clicked,
            this, &MainSAEHMIApp::onbtnInjectionTest_clicked);
    connect(ui->btnBackTest, &QToolButton::clicked, this, &MainSAEHMIApp::onbtnBackTest_clicked);
    connect(ui->btnCommTest, &QToolButton::clicked, this, &MainSAEHMIApp::onbtnCommTest_clicked);

    ui->mainStackedWindow->setCurrentWidget(ui->widPilotView);
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::createWindows()
{
    QStringList tests;
    tests << "Front Test";
    tests << "Back Test";
    tests << "Injection Test";
    tests << "Turbo Test";

    testsWindows.insert("Pilot View", ui->widPilotView);
    for(const auto& test: tests)
    {
        BaseTestWindow* widTest = new BaseTestWindow(ui->mainStackedWindow);
        widTest->setTitle(test);
        ui->mainStackedWindow->addWidget(widTest);
        testsWindows.insert(test, widTest);
    }
    testsWindows.insert("Comm Test", ui->widCommTest);
}
//--------------------------------------------------------------------------------------------------
MainSAEHMIApp::~MainSAEHMIApp()
{
    delete ui;
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::onbtnPilotView_clicked()
{
    QWidget* wid{testsWindows.value("Pilot View")};
    ui->mainStackedWindow->setCurrentWidget(wid);
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::onbtnFrontTest_clicked()
{
    QWidget* wid{testsWindows.value("Front Test")};
    ui->mainStackedWindow->setCurrentWidget(wid);
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::onbtnTurboTest_clicked()
{
    QWidget* wid{testsWindows.value("Turbo Test")};
    ui->mainStackedWindow->setCurrentWidget(wid);
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::onbtnInjectionTest_clicked()
{
    QWidget* wid{testsWindows.value("Injection Test")};
    ui->mainStackedWindow->setCurrentWidget(wid);
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::onbtnBackTest_clicked()
{
    QWidget* wid{testsWindows.value("Back Test")};
    ui->mainStackedWindow->setCurrentWidget(wid);
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::onbtnCommTest_clicked()
{
    QWidget* wid{testsWindows.value("Comm Test")};
    ui->mainStackedWindow->setCurrentWidget(wid);
}
//--------------------------------------------------------------------------------------------------
