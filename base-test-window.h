#ifndef BASETESTWINDOW_H
#define BASETESTWINDOW_H

#include <QWidget>

namespace Ui
{
    class MainTestWindow;
}

class BaseTestWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit BaseTestWindow(QWidget* parent);
        ~BaseTestWindow();

        void setTitle(const QString& title);

    private:
        Ui::MainTestWindow* ui;

    signals:

    private slots:
        void nextPage();
};

#endif // BASETESTWINDOW_H
