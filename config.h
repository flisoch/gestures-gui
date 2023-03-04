#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class Config : public QObject
{
    Q_OBJECT
public:
    Config();
    void readCommands(QString text);
    QJsonObject json;
signals:
    void configFileRead(QJsonObject* json);
public slots:
    void saveCommands();
};

#endif // CONFIG_H
