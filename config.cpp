#include <QJsonDocument>
#include <QDebug>
#include "config.h"

Config::Config()
{

}

void Config::saveCommands()
{
    // todo: QJsonObject to QText
//    QString text = json.
}

void Config::readCommands(QString text)
{
//    QJsonObject config = QJsonDocument::fromJson(text.toUtf8()).object();
    this->json = QJsonDocument::fromJson(text.toUtf8()).object();
    emit configFileRead(&this->json);
}
