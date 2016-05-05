import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Extras 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

ApplicationWindow {
    id: applicationWindow1
    visible: true
    toolBar:ToolBar {
        RowLayout {
            anchors.bottomMargin: -51
            anchors.fill: parent
            ToolButton {
                width: 44
                height: 60
                text: "ciao"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                scale: 1
                activeFocusOnPress: false
                checkable: true
                iconSource: "regression.png"
            }
            ToolButton {
                iconSource: "open.png"
            }
            ToolButton {
                iconSource: "save-as.png"
            }
            Item { Layout.fillWidth: true }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
        }
    }
}
