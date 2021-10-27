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
    explicit GesturesView(QWidget *parent = nullptr);
    ~GesturesView();

private:
    Ui::GesturesView *ui;

};

#endif // GESTURESVIEW_H
