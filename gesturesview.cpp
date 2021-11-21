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
    copyCommandsFromConfigFile(fingersCount);
}

GesturesView::~GesturesView()
{
    delete ui;
}

void GesturesView::copyCommandsFromConfigFile(int fingersCount)
{
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
    QJsonDocument config = QJsonDocument::fromJson(text.toUtf8());
    QJsonObject o = config.object();
    QJsonValue value = o.value(QString("touchpad")).toObject().value("swipe");
    qInfo() << value;
    QString key = QString::number(fingersCount);
    value = value.toObject().value(key).toObject().value("u").toObject().value("end");
    qInfo() << value;
    QJsonArray array = value.toArray();
    QString command;
    foreach(QJsonValue val, array) {
        command += val.toString() + ",";
    }
    command.chop(1);
    qInfo() <<command;
    ui->swipe_up->setText(command);
}
