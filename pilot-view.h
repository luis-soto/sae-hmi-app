#ifndef PILOTVIEW_H
#define PILOTVIEW_H

#include <QWidget>

namespace Ui {
class PilotView;
}

class PilotView : public QWidget
{
    Q_OBJECT

public:
    explicit PilotView(QWidget *parent = nullptr);
    ~PilotView();

private:
    Ui::PilotView *ui;
};

#endif // PILOTVIEW_H
