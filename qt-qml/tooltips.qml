//import QtQuick 1.0
import Qt 4.7
 
Rectangle {
    width: 200
    height: 200
 
    property bool needTooltip: button.hovered
    property real tooltipX: button.x
    property real tooltipY: button.y
 
    Rectangle {
        id: button
        property bool hovered: ma.containsMouse
        width: 100; height: 100
        anchors.centerIn: parent
        color: "steelblue"
        Text {
            anchors.centerIn: parent
            text: "My Button"
        }
        MouseArea {
            id: ma
            anchors.fill: parent
            hoverEnabled: true
        }
    }
 
    Rectangle {
        id: tooltip
        width: 75; height: 20
        visible: false
        color: "red"
        Text {
            anchors.centerIn: parent
            text: "My Tooltip"
        }
 
        states: State {
            name: "inuse"
            when: needTooltip
            PropertyChanges {
                target: tooltip
                visible: true
                x: tooltipX + 12
                y: tooltipY - 30
            }
        }
    }
}
