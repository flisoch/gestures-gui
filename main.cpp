#include "gesturesgui.h"

#include <QApplication>
#include <QLocale>
#include <QSettings>
#include <QTranslator>

void setupSettings() {
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue("configPath", "/.config/gestures.conf");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "gestures-gui_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    setupSettings();
    GesturesGui w;
    w.show();
    return a.exec();
}
