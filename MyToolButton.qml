import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
id: myToolButton

property string text
property string source
property bool hovered
property bool clicked

width: 90
height: 93
color: "transparent"
border.width: 1
border.color: myToolButton.clicked ? "gold" : myToolButton.hovered ? "gold" : "transparent"
radius: 10

Image {
    id: myToolButtonIcon
    source: myToolButton.source
    y: myToolButton.y + 5
    anchors.horizontalCenter: myToolButton.horizontalCenter
}

Text {
    text: myToolButton.text
    y: myToolButtonIcon.y + myToolButtonIcon.height + 3
    anchors.horizontalCenter: myToolButtonIcon.horizontalCenter
}
}
