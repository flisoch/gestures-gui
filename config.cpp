#include <QJsonDocument>
#include <QDebug>
#include <QProcess>
#include "config.h"

Config::Config()
{

}

void Config::saveCommands()
{
    if (QProcess::execute(QString("/bin/sh ") + "/home/flisoch/.config/gestures-ui/restart_gestures.sh") < 0)
        qDebug() << "Failed to run";
}

void Config::readCommands(QString text)
{
    this->json = QJsonDocument::fromJson(text.toUtf8()).object();
    emit configFileRead(&this->json);
}
