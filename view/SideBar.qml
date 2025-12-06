import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {

    property var items: []


    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(45/255, 71/255, 112/255, 1)


        ColumnLayout {
            anchors.fill: parent
            anchors.topMargin: parent.width * 2
            spacing: parent.height * 0.1

            Repeater {
                model: items

                delegate: Rectangle {


                }
            }

        }


    }

}
