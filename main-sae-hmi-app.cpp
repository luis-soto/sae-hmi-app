#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QPushButton>
//--------------------------------------------------------------------------------------------------
#include "main-sae-hmi-app.h"
#include "ui_main-sae-hmi-app.h"
//--------------------------------------------------------------------------------------------------
MainSAEHMIApp::MainSAEHMIApp(QWidget* parent): QWidget{parent}, ui{new Ui::MainSAEHMIApp}
{
    ui->setupUi(this);

    createWindows();
}
//--------------------------------------------------------------------------------------------------
void MainSAEHMIApp::createWindows()
{
    QFile file;
    file.setFileName("saeconfig.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString config{file.readAll()};
    file.close();

    QJsonDocument doc{QJsonDocument::fromJson(config.toUtf8())};
    QJsonObject saeConfig{doc.object()};

    QJsonValue tests{saeConfig.value("tests")};
    QJsonArray arrayTests = tests.toArray();

    // TODO: criar ui para o modo visão do piloto
    addPageToStackedWindow("Pilot View");

    foreach(const QJsonValue& test, arrayTests)
    {
        const QString testName = test.toObject().value("name").toString();
        BaseTestWindow* widTest{addPageToStackedWindow(testName)};

        QJsonValue variables{test.toObject().value("variables")};
        QJsonArray arrayVariables = variables.toArray();

        foreach(const QJsonValue& variable, arrayVariables)
        {
            const QString varName{variable.toObject().value("name").toString()};
            const qint32 varID{variable.toObject().value("id").toInt()};
            widTest->addPlot(varName, varID);
        }

        widTest->mountView();
    }

    // TODO: criar ui para o teste de comunicação
    addPageToStackedWindow("Comm Test");

    ui->mainStackedWindow->setCurrentIndex(0);
}
//--------------------------------------------------------------------------------------------------
MainSAEHMIApp::~MainSAEHMIApp()
{
    delete ui;
}
//--------------------------------------------------------------------------------------------------
BaseTestWindow* MainSAEHMIApp::addPageToStackedWindow(const QString& windowTitle)
{
    BaseTestWindow* wid{new BaseTestWindow(ui->mainStackedWindow, windowTitle)};

    QPushButton* btn{new QPushButton(windowTitle, this)};

    connect(btn, &QPushButton::clicked, this, [=]()
    {
        ui->mainStackedWindow->setCurrentWidget(wid);
    });

    ui->layButtons->addWidget(btn);
    ui->mainStackedWindow->addWidget(wid);

    return wid;
}
//--------------------------------------------------------------------------------------------------
