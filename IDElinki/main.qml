import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 800
    height: 600

    Rectangle {
        id:area
        color: "#26c6c4"
        anchors.fill: parent
        border.color: "#0f0d0d"

        Dock {
            id: dock
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
        }

        WorkPlace{
            id:workplace
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: dock.right
            z:0

        }

    }
}
