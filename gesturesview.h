#ifndef GESTURESVIEW_H
#define GESTURESVIEW_H

#include <QWidget>


namespace Ui {
class GesturesView;
}

class GesturesView : public QWidget
{
    Q_OBJECT

public:
    explicit GesturesView(QWidget *parent = nullptr, int fingersCount = 1);
    ~GesturesView();

private:
    Ui::GesturesView *ui;
    void copyCommandsFromConfigFile(int fingersCount);
};

#endif // GESTURESVIEW_H
