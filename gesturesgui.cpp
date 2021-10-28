#include "gesturesgui.h"
#include "./ui_gesturesgui.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
GesturesGui::GesturesGui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GesturesGui)
{
    ui->setupUi(this);
    QWidget *tab1 = ui->tab;
    gestureview = new GesturesView(tab1);
    gestureview = new GesturesView(ui->tab_2);
    gestureview = new GesturesView(ui->tab_3);
    gestureview = new GesturesView(ui->tab_4);
}

GesturesGui::~GesturesGui()
{
    delete ui;
}


void GesturesGui::on_pushButton_clicked()
{
    QString filename =  QFileDialog::getOpenFileName(this, "Select config file", QDir::homePath());
//    QMessageBox::information(this, "..", filename);
    QFile file(filename);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    qWarning() << text;
    QByteArray json_bytes = text.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()) {
        qWarning() << "Failed to create JSON doc.";

    }
    if (!json_doc.isObject()) {
        qWarning() << "JSON is not an object.";
    }

    QJsonObject json_obj = json_doc.object();

    if (json_obj.isEmpty()) {
        qWarning()  << "JSON object is empty.";
    }

    // step 4
    auto result = json_obj.toVariantMap();
    qWarning() << result;
    text.replace("'", "\"");
    //    text.replace("\n", "");
    //    text.replace(" ", "");
    qWarning() << text;
    QJsonDocument config = QJsonDocument::fromJson(text.toUtf8());
    qWarning() << config;
    qWarning() << config.toJson(QJsonDocument::Indented);
    QJsonObject o = config.object();
    qWarning() << o;
    QJsonValue value = o.value(QString("touchpad"));
    qWarning() << value;

}

