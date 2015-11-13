import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: dock
    width: 100
    height: 62
    MouseArea {
        anchors.fill: parent
    }
    ScrollView {
        anchors.fill: parent
        contentItem: ColumnLayout{
            Stat {
                width: 64
                height: 64
                name: "if_stat"
                dragable: true
                z:100
            }
            Stat {
                width: 64
                height: 64
                name: "loop"
                dragable: true
            }
        }
    }
}
