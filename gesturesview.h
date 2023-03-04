#ifndef GESTURESVIEW_H
#define GESTURESVIEW_H

#include <QWidget>
#include "config.h"

namespace Ui {
class GesturesView;
}

class GesturesView : public QWidget
{
    Q_OBJECT

public:
    explicit GesturesView(QWidget *parent = nullptr, int fingersCount = 1);
    ~GesturesView();

    Config *config = nullptr;

private slots:
    void setConfig(QJsonObject *json);
    void reloadGestures();

private:

    Ui::GesturesView *ui;
    int fingersCount;
    void readPinchCommands(QJsonValue value);
    void readSwipeCommands(QJsonValue value);
    void readCommandsFromConfigFile();
    QString readCommandStart(QJsonObject value);
    QString readCommandUpdate(QJsonObject value);
    QString readCommandEnd(QJsonObject value);
    void setCommand(QString direction, QJsonObject command);
    QString readConfigFile();
};

#endif // GESTURESVIEW_H
