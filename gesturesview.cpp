#include "gesturesview.h"
#include "ui_gesturesview.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


GesturesView::GesturesView(QWidget *parent, int fingersCount) :
    QWidget(parent),
    ui(new Ui::GesturesView)
{
    ui->setupUi(this);
    this->fingersCount = fingersCount;
    copyCommandsFromConfigFile();
}

GesturesView::~GesturesView()
{
    delete ui;
}

QString GesturesView::copyCommandStart(QJsonObject value) {

    QJsonArray array = value["start"].toArray();
    QString command;
    foreach(QJsonValue val, array) {
        command += val.toString() + ",";
    }
    command.chop(1);
    qDebug() << command;
    return command;
}

QString GesturesView::copyCommandUpdate(QJsonObject value) {
    return "";
}

QString GesturesView::copyCommandEnd(QJsonObject value) {
    QJsonArray array = value["end"].toArray();
    QString command;
    foreach(QJsonValue val, array) {
        command += val.toString() + ",";
    }
    command.chop(1);
    return command;
}

void GesturesView::setCommand(QString direction, QString command) {
    if (direction == "l") {
        ui->left_command->setText(command);
    }
    else if (direction == "r") {
        ui->swipe_right_command->setText(command);
    }
    else if (direction == "u") {
        ui->swipe_up_command->setText(command);
    }
    else if (direction == "d") {
        ui->swipe_down_command->setText(command);
    }
    else if (direction == "lu") {
        ui->swipe_up_left_command->setText(command);
    }
    else if (direction == "rd") {
        ui->swipe_down_right_command->setText(command);
    }
    else if (direction == "ld") {
        ui->swipe_down_left_command->setText(command);
    }
    else if (direction == "ru") {
        ui->swipe_up_right_command->setText(command);
    }
}

void GesturesView::copySwipeCommands(QJsonValue swipeCommands) {
    QString key = QString::number(fingersCount);
    swipeCommands = swipeCommands.toObject()[key];
    QJsonObject commands =  swipeCommands.toObject();
    foreach(const QString& direction, commands.keys()) {
       qDebug() << direction;
       QJsonObject value = commands.value(direction).toObject();
       QString command;
       command += copyCommandStart(value);
       command += copyCommandUpdate(value);
       command += copyCommandEnd(value);
       setCommand(direction, command);
       qDebug() << command;
    }
}

void GesturesView::copyPinchCommands(QJsonValue value) {

    ui->pinch_in->setText("pinch");
}

QString GesturesView::readConfigFile() {
    QString homePath = QDir::homePath();
    QFile file(homePath + "/.config/gestures.conf");

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

void GesturesView::copyCommandsFromConfigFile()
{
    QString text = readConfigFile();
    QJsonObject config = QJsonDocument::fromJson(text.toUtf8()).object();

    QJsonValue commands = config["touchpad"].toObject()["swipe"];
    copySwipeCommands(commands);
    commands = config["touchpad"].toObject()["pinch"];
    copyPinchCommands(commands);
}
