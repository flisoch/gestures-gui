#include "gesturesview.h"
#include "gesturesgui.h"
#include "ui_gesturesview.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QDebug>
#include <QPushButton>
#include "config.h"

GesturesView::GesturesView(QWidget *parent, int fingersCount, Config *c) :
    QWidget(parent),
    ui(new Ui::GesturesView),
    config{*c}
{
    ui->setupUi(this);
    this->fingersCount = fingersCount;
    connect(ui->saveConfigButton, &QPushButton::released, &this->config, &Config::saveCommands);
    connect(&this->config, &Config::configFileRead, this, &GesturesView::setConfig);
    readCommandsFromConfigFile();
}

GesturesView::~GesturesView()
{
    delete ui;
}


QString GesturesView::readCommandStart(QJsonObject value) {

    QJsonArray array = value["start"].toArray();
    QString command;
    foreach(QJsonValue val, array) {
        command += val.toString() + ",";
    }
    command.chop(1);
    return command;
}

QString GesturesView::readTap(QJsonArray value) {
    QString command;
    foreach(QJsonValue val, value) {
        command += val.toString() + ",";
    }
    command.chop(1);
    return command;
}

QString GesturesView::readCommandUpdate(QJsonObject value) {
    return "";
}

QString GesturesView::readCommandEnd(QJsonObject value) {
    QJsonArray array = value["end"].toArray();
    QString command;
    foreach(QJsonValue val, array) {
        command += val.toString() + ",";
    }
    command.chop(1);
    return command;
}

void GesturesView::setCommand(QString direction, QJsonObject command) {
    if (direction == "l") {
        ui->swipe_left_start->setText(readCommandStart(command));
        ui->swipe_left_update->setText(readCommandUpdate(command));
        ui->swipe_down_left_end->setText(readCommandEnd(command));
    }
    else if (direction == "r") {
        ui->swipe_right_start->setText(readCommandStart(command));
        ui->swipe_right_update->setText(readCommandUpdate(command));
        ui->swipe_right_end->setText(readCommandEnd(command));
    }
    else if (direction == "u") {
        ui->swipe_up_start->setText(readCommandStart(command));
        ui->swipe_up_update->setText(readCommandUpdate(command));
        ui->swipe_up_end->setText(readCommandEnd(command));
    }
    else if (direction == "d") {
        ui->swipe_down_start->setText(readCommandStart(command));
        ui->swipe_down_update->setText(readCommandUpdate(command));
        ui->swipe_down_end->setText(readCommandEnd(command));
    }
    else if (direction == "lu") {
        ui->swipe_up_left_start->setText(readCommandStart(command));
        ui->swipe_up_left_update->setText(readCommandUpdate(command));
        ui->swipe_up_left_end->setText(readCommandEnd(command));
    }
    else if (direction == "rd") {
        ui->swipe_down_right_start->setText(readCommandStart(command));
        ui->swipe_down_right_update->setText(readCommandUpdate(command));
        ui->swipe_down_right_end->setText(readCommandEnd(command));
    }
    else if (direction == "ld") {
        ui->swipe_down_left_start->setText(readCommandStart(command));
        ui->swipe_down_left_update->setText(readCommandUpdate(command));
        ui->swipe_down_left_end->setText(readCommandEnd(command));
    }
    else if (direction == "ru") {
        ui->swipe_up_right_start->setText(readCommandStart(command));
        ui->swipe_up_right_update->setText(readCommandUpdate(command));
        ui->swipe_up_right_end->setText(readCommandEnd(command));
    }
}



void GesturesView::readPinchCommands(QJsonValue value) {

//    ui->pinch_in_start->setText("pinch");
}

QString GesturesView::readConfigFile() {
    QString homePath = QDir::homePath();
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    QFile file(homePath + settings.value(SETTING_CONFIG_PATH).toString());

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
    return text;
}

void GesturesView::setConfig(QJsonObject* json)
{
    QJsonValue commands = (*json)["touchpad"].toObject()["swipe"];
    readSwipeCommands(commands);
    commands = (*json)["touchpad"].toObject()["pinch"];
    readPinchCommands(commands);
}

void GesturesView::readSwipeCommands(QJsonValue swipeCommands) {
   QString key = QString::number(fingersCount);
   swipeCommands = swipeCommands.toObject()[key];
   QJsonObject commands =  swipeCommands.toObject();
   foreach(const QString& direction, commands.keys()) {
      qDebug() << direction;
      if (direction == "t") {
          ui->tap->setText(readTap(commands.value(direction).toArray()));
      }
      QJsonObject command = commands.value(direction).toObject();
      setCommand(direction, command);
      qDebug() << command;
   }
}



void GesturesView::readCommandsFromConfigFile()
{
    QString text = readConfigFile();
    this->config.readCommands(text);
}


void GesturesView::reloadGestures()
{

}
