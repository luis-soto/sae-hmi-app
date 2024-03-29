#ifndef BASETESTWINDOW_H
#define BASETESTWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QList>

namespace Ui
{
    class MainTestWindow;
}

class BaseTestWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit BaseTestWindow(QWidget* parent, const QString& title);
        ~BaseTestWindow();

        void addPlot(const QString& title, const qint32 id);
        void setTitle(const QString& title);
        void mountView();

    private:
        Ui::MainTestWindow* ui;
        QList<QWidget*> _plots;

    signals:
        void visibilityChanged();

    private slots:
        void on_btnNextPage_clicked();
};

#endif // BASETESTWINDOW_H
