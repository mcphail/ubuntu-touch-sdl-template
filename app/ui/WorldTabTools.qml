import QtQuick 2.0
import Ubuntu.Components 1.1

ToolbarItems {
    ToolbarButton {
        iconSource: Qt.resolvedUrl("../graphics/toolbarIcon.png")
        text: i18n.tr("Tap me!")

        onTriggered: {
            label.text = i18n.tr("Toolbar tapped")
        }
    }
}

