#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "configManager/sizeconfigmanager.h"
#include "configManager/colorconfigmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Config size
    SizeConfigManager *sizeManager = new SizeConfigManager();
    sizeManager->loadFile(":/config/config/size_config.json");

    // Config color
    ColorConfigManager *colorManager = new ColorConfigManager();

    // General config


    // For DBthread


    // UIThread is main thread


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("storeApp", "Main");

    return app.exec();
}
