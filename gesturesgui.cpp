#include "gesturesgui.h"
#include "./ui_gesturesgui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QDebug>
//#include <QInfo>
#include <QTextStream>

GesturesGui::GesturesGui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GesturesGui)
{
    ui->setupUi(this);

    QHBoxLayout *layout = new QHBoxLayout(ui->tab);
    gestureview = new GesturesView(ui->tab, 2);
    layout->addWidget(gestureview);

    layout = new QHBoxLayout(ui->tab_2);
    gestureview = new GesturesView(ui->tab_2, 3);
    layout->addWidget(gestureview);

    layout = new QHBoxLayout(ui->tab_3);
    gestureview = new GesturesView(ui->tab_3, 4);
    layout->addWidget(gestureview);

    layout = new QHBoxLayout(ui->tab_4);
    gestureview = new GesturesView(ui->tab_4, 5);
    layout->addWidget(gestureview);
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
    qDebug() << value;

}

