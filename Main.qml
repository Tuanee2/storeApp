import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "view"

Window {
    visible: true
    visibility: Window.FullScreen

    SideBar {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        width: parent.width * 0.05
        height: parent.height
    }

}
