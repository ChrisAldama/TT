import QtQuick 2.0

Item {
    id: root
    property string name: ""
    property bool dragActive: dragArea.drag.active
    property bool dragable: false

    onDragActiveChanged: {
        if (dragActive) {
            print("drag started")
            Drag.start();
        } else {
            print("drag finished", parent)
            Drag.drop();
        }
    }
    Drag.dragType: Drag.Automatic

    Image {
        id: back
        source: "image://olinki/" + name
        width: parent.width
        height: parent.height
        sourceSize.width: width
        sourceSize.height: height
    }
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: root.dragable?parent:null
    }
}
