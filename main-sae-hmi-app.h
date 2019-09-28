#ifndef MAINSAEHMIAPP_H
#define MAINSAEHMIAPP_H

#include <QWidget>
#include <QMap>

namespace Ui
{
    class MainSAEHMIApp;
}

class MainSAEHMIApp : public QWidget
{
    Q_OBJECT

    public:
        MainSAEHMIApp(QWidget *parent = nullptr);
        ~MainSAEHMIApp();

    private:
        Ui::MainSAEHMIApp* ui;
        QMap<QString, QWidget*> testsWindows;

        void createWindows();

    public slots:
        void onbtnPilotView_clicked();
        void onbtnFrontTest_clicked();
        void onbtnTurboTest_clicked();
        void onbtnInjectionTest_clicked();
        void onbtnBackTest_clicked();
        void onbtnCommTest_clicked();
};

#endif // MAINSAEHMIAPP_H
