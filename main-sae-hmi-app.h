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
        MainSAEHMIApp(QWidget* parent = nullptr);
        ~MainSAEHMIApp();

    private:
        Ui::MainSAEHMIApp* _ui;

        QWidget* addPageToStackedWindow(const QString& windowTitle);

        void addPageToStackedWindow(QWidget* const wid);

        void initializePilotView();

        void initializeTests();

        void initializeSystemConfiguration();
};

#endif // MAINSAEHMIAPP_H
