#include "sizeconfigmanager.h"

SizeConfigManager::SizeConfigManager() {}


bool SizeConfigManager::loadFile(const QString& fileName){
    QFile file = QFile(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();


    // FOR SIDEBAR
    QJsonObject sidebar = root["SIDEBAR"].toObject();
    this->sideBar.width_ratio = sidebar["WIDTH_RATIO"].toDouble();
    this->sideBar.height_ratio = sidebar["HEIGHT_RATIO"].toDouble();

    file.close();
    return true;
}
