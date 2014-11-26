import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    id: root
    property int dw: 257
    property int dh: 87

    ScrollView{
        anchors.fill: parent
        contentItem: ColumnLayout{
            Stat {
                id:begin
                name: "inicio"
                width: dw
                height: dh
            }

            Stat {
                name: "end"
                id:end
                width: dw
                height: dh
            }
        }
    }
}
