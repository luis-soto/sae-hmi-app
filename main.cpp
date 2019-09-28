#include "main-sae-hmi-app.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSAEHMIApp app;
    app.show();
    return a.exec();
}
