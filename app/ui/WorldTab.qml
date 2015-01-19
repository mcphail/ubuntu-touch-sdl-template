import QtQuick 2.0
import Ubuntu.Components 1.1
import "../components"

Tab {
    title: i18n.tr("..World!")

    page: Page {
        tools: WorldTabTools {
            objectName: "worldTab_tools"
        }

        Column {
            spacing: units.gu(2)
            anchors.centerIn: parent

            HelloComponent {
                objectName: "worldTab_HelloComponent"

                anchors.horizontalCenter: parent.horizontalCenter

                text: i18n.tr("WorldTab")
            }

            Label {
                id: label
                objectName: "worldTab_label"

                anchors.horizontalCenter: parent.horizontalCenter

                text: i18n.tr("Swipe from bottom to up to reveal the toolbar.")
            }
        }
    }
}

