#ifndef GESTURESGUI_H
#define GESTURESGUI_H

#include <QMainWindow>
#include "gesturesview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GesturesGui; }
QT_END_NAMESPACE

class GesturesGui : public QMainWindow
{
    Q_OBJECT

public:
    GesturesGui(QWidget *parent = nullptr);
    ~GesturesGui();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GesturesGui *ui;
    GesturesView *gestureview;
};
#endif // GESTURESGUI_H
