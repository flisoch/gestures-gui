#include "gesturesgui.h"
#include "./ui_gesturesgui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QDebug>
#include <QTextStream>
#include <QAction>

GesturesGui::GesturesGui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GesturesGui)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout(ui->tab_1);
    gestureview = new GesturesView(ui->tab_1, 3);
    layout->addWidget(gestureview);

    layout = new QHBoxLayout(ui->tab_2);
    gestureview = new GesturesView(ui->tab_2, 4);
    layout->addWidget(gestureview);

    layout = new QHBoxLayout(ui->tab_3);
    gestureview = new GesturesView(ui->tab_3, 5);
    layout->addWidget(gestureview);

    connect(ui->actionSet_config_file, &QAction::triggered, this, &GesturesGui::onConfigSettingClicked);
}

GesturesGui::~GesturesGui()
{
    delete ui;
}


void GesturesGui::onConfigSettingClicked()
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

