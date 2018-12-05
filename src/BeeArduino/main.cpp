#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "arduino.h"
#include <QtQml>
#include "core/views/mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("arduino", new Arduino());
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
//    Arduino arduino;
//    arduino.start();
    MainWindow w;
    w.showMaximized();

    return app.exec();
}
