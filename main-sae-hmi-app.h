#ifndef MAINSAEHMIAPP_H
#define MAINSAEHMIAPP_H

#include <QWidget>
#include <QMap>
#include "base-test-window.h"

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
        Ui::MainSAEHMIApp* ui;

        BaseTestWindow* addPageToStackedWindow(const QString& windowTitle);
        void createWindows();
};

#endif // MAINSAEHMIAPP_H
