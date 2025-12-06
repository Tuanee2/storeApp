#ifndef SIZECONFIGMANAGER_H
#define SIZECONFIGMANAGER_H

#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>


struct SideBar {
    double width_ratio;
    double height_ratio;
};

struct Dashboard {
    double width_ratio;
    double height_ratio;
};

class SizeConfigManager
{
public:
    SizeConfigManager();
    bool loadFile(const QString& fileName);

public:
    SideBar sideBar;
    Dashboard dashBoard;
};

#endif // SIZECONFIGMANAGER_H
