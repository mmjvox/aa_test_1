import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs


Column{
    property string imagePath:"";

    Image {
        id: img1
        width: 200;
        height: width;
    }

    Button{
        text: "select"
        onClicked: fileDialog.open();
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted: img1.source = imagePath = selectedFile;
    }
}
