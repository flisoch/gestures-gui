#ifndef GESTURESVIEW_H
#define GESTURESVIEW_H

#include <QWidget>


namespace Ui {
class GesturesView;
}

class GesturesView : public QWidget
{
    Q_OBJECT

public:
    explicit GesturesView(QWidget *parent = nullptr, int fingersCount = 1);
    ~GesturesView();

private:
    Ui::GesturesView *ui;
    int fingersCount;
    void copyPinchCommands(QJsonValue value);
    void copySwipeCommands(QJsonValue value);
    void copyCommandsFromConfigFile();
    QString copyCommandStart(QJsonObject value);
    QString copyCommandUpdate(QJsonObject value);
    QString copyCommandEnd(QJsonObject value);
    void setCommand(QString direction, QString command);
    QString readConfigFile();
};

#endif // GESTURESVIEW_H
