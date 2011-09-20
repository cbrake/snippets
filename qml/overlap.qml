import Qt 4.7

Rectangle {
    width: 1024
    height: 768

    Rectangle {
        id: rect1
        x: 200
        y: 200
        width: 200
        height: 200

        color: "red"
        border.color: "black"
        border.width: 3
        z: 200
        //opacity: 0

        Behavior on opacity {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
                duration: 250
            }
        }

    }

    Text {
        x: 150
        y: 250
        text: "Hi this is a test"
        font.pointSize: 40
    }

    MouseArea {
        anchors.fill: parent
        onEntered: { 
            console.log("entered");
            rect1.opacity = 1 
        }

        onExited: { 
            rect1.opacity = 0 
            console.log("exitted");
        }
        hoverEnabled: true
    }

    Rectangle {
        x: 250
        y: 250
        width: 200
        height: 200

        color: "yellow"
        border.color: "black"
        border.width: 3
        opacity: 1
    }


}
