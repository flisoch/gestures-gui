#include "gesturesview.h"
#include "ui_gesturesview.h"

GesturesView::GesturesView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GesturesView)
{
    ui->setupUi(this);
}

GesturesView::~GesturesView()
{
    delete ui;
}
