#include "main-sae-hmi-app.h"
#include "ui_main-sae-hmi-app.h"
#include "base-test-window.h"
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
//--------------------------------------------------------------------------------------------------
MainSAEHMIApp::MainSAEHMIApp(QWidget* parent): QWidget{parent}, _ui{new Ui::MainSAEHMIApp}
{
    _ui->setupUi(this);

    initializePilotView();
    initializeTests();
    initializeSystemConfiguration();

    _ui->mainStackedWindow->setCurrentIndex(0);
}
//--------------------------------------------------------------------------------------------------
MainSAEHMIApp::~MainSAEHMIApp()
{
    delete _ui;
}
//--------------------------------------------------------------------------------------------------
QWidget* MainSAEHMIApp::addPageToStackedWindow(const QString& windowTitle)
{
    BaseTestWindow* const wid{new BaseTestWindow(_ui->mainStackedWindow, windowTitle)};

    addPageToStackedWindow(wid);

    return wid;
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::addPageToStackedWindow(QWidget* const wid)
{
    const QString titleFieldName{"lblTitle"};

    if(wid != nullptr)
    {
        QLabel* const lblTitle{wid->findChild<QLabel*>(titleFieldName)};

        const QString windowTitle{(lblTitle != nullptr) ? lblTitle->text() : ""};

        QPushButton* btn{new QPushButton(windowTitle, this)};

        connect(btn, &QPushButton::clicked, this, [=]()
        {
            _ui->mainStackedWindow->setCurrentWidget(wid);
        });

        BaseTestWindow* const testWindow{dynamic_cast<BaseTestWindow*>(wid)};
        if(testWindow != nullptr)
        {
            connect(_ui->mainStackedWindow, &QStackedWidget::currentChanged,
                    testWindow, &BaseTestWindow::visibilityChanged);
        }

        _ui->layButtons->addWidget(btn);
        _ui->mainStackedWindow->addWidget(wid);
    }
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::initializePilotView()
{
    // TODO: create ui for pilot view mode
    addPageToStackedWindow("Pilot View");
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::initializeTests()
{
    QFile file;
    file.setFileName("/home/luis/projects/sae-hmi-app/saeconfig.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString config{file.readAll()};
    file.close();

    QJsonObject saeConfig{QJsonDocument::fromJson(config.toUtf8()).object()};

    const QJsonArray tests = saeConfig.value("tests").toArray();

    foreach(const QJsonValue& test, tests)
    {
        const QString testName{test.toObject().value("name").toString()};
        BaseTestWindow* const widTest{dynamic_cast<BaseTestWindow*>(addPageToStackedWindow(testName))};

        const QJsonArray variables = test.toObject().value("variables").toArray();

        foreach(const QJsonValue& variable, variables)
        {
            const QString varName{variable.toObject().value("name").toString()};
            const qint32 varID{variable.toObject().value("id").toInt()};
            widTest->addPlot(varName, varID);
        }

        widTest->mountView();
    }
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::initializeSystemConfiguration()
{
    // TODO: create ui for system configuration
    addPageToStackedWindow("System Configuration");
}
//--------------------------------------------------------------------------------------------------
