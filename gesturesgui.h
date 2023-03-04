#ifndef GESTURESGUI_H
#define GESTURESGUI_H

#include <QMainWindow>
#include "gesturesview.h"
#include "config.h"

#define ORGANIZATION_NAME "gestures-ui"
#define ORGANIZATION_DOMAIN "www.example.com"
#define APPLICATION_NAME "Gestures GUI"
#define SETTING_CONFIG_PATH "configPath"

QT_BEGIN_NAMESPACE
namespace Ui { class GesturesGui; }
QT_END_NAMESPACE

class GesturesGui : public QMainWindow
{
    Q_OBJECT

public:
    GesturesGui(QWidget *parent = nullptr);
    ~GesturesGui();
signals:
    void configFileChanged();
private slots:
    void onConfigSettingClicked();

private:
    Ui::GesturesGui *ui;
    GesturesView *gestureview;
    Config *config = nullptr;
};
#endif // GESTURESGUI_H
