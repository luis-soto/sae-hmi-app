#ifndef BASEPLOT_H
#define BASEPLOT_H

#include <QWidget>

namespace Ui
{
    class BasePlot;
}

class BasePlot : public QWidget
{
    Q_OBJECT
    public:
        BasePlot(const QString& title, const qint32 id, QWidget* parent);
        ~BasePlot();

        void setTitle(const QString& title);

        qint32 getID() const;

        const QString& getTitle() const;

    private:
        Ui::BasePlot* ui;
        qint32 _id;
        QString _title;
        QVector<qreal> dataX;
        QVector<qreal> dataY;

    signals:

    public slots:
        void newDataReceived(const qint32 id, const qint32 data);
};

#endif // BASEPLOT_H
