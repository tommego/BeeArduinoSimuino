#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "arduino.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("arduino", new Arduino());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
//    Arduino arduino;
//    arduino.start();

    return app.exec();
}
