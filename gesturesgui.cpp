#include "gesturesgui.h"
#include "./ui_gesturesgui.h"


GesturesGui::GesturesGui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GesturesGui)
{
    ui->setupUi(this);
    QWidget *tab1 = ui->tab;
    gestureview = new GesturesView(tab1);
    gestureview = new GesturesView(ui->tab_2);
    gestureview = new GesturesView(ui->tab_3);
    gestureview = new GesturesView(ui->tab_4);
}

GesturesGui::~GesturesGui()
{
    delete ui;
}

