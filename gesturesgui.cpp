#include "gesturesgui.h"
#include "./ui_gesturesgui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

GesturesGui::GesturesGui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GesturesGui)
{
    ui->setupUi(this);
    QWidget *tab1 = ui->tab;
    gestureview = new GesturesView(tab1, 2);
    gestureview = new GesturesView(ui->tab_2, 3);
    gestureview = new GesturesView(ui->tab_3, 4);
    gestureview = new GesturesView(ui->tab_4, 5);
}

GesturesGui::~GesturesGui()
{
    delete ui;
}


void GesturesGui::on_pushButton_clicked()
{
    QString filename =  QFileDialog::getOpenFileName(this, "Select config file", QDir::homePath());

    QFile file(filename);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    QString text;
    while (!in.atEnd())
       {
          QString line = in.readLine();
          if (line.contains("#")) {
              continue;
          }
          text += line;
       }
    file.close();
    text.replace("'", "\"");
    QJsonDocument config = QJsonDocument::fromJson(text.toUtf8());
    QJsonObject o = config.object();
    QJsonValue value = o.value(QString("touchpad"));
    qInfo() << value;

}

