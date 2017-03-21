import QtQuick 2.0
import QtQuick.Controls 2.1

Popup {
        id: popup
        width: 200
        height: 300
        modal: true
        focus: true
        closePolicy:Popup.CloseOnReleaseOutside| Popup.CloseOnReleaseOutsideParent |Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
}
