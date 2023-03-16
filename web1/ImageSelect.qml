import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import ApiServer
import WasmFileDialog

Rectangle{
    width: childrenRect.width;
    height: childrenRect.height;
    border.width: 1;

    property string imagePath:"";

    WasmFileDialog{
        id: wasmFileDialog;
        onAccepted: (fileContent, fileName, base64)=>{
            img1.source=base64;
            apiServer.sendSample(fileContent, fileName);
        }
    }

    ApiServer{
        id: apiServer;
    }

    DropArea{
        anchors.fill: parent;

        onDropped: (drop)=>{
            img1.source = imagePath = drop.text;
            apiServer.sendSample(imagePath);
        }
    }

    Column{

        Image {
            id: img1
            width: 200;
            height: width;
        }

        Row{
            spacing: 16;
            Button{
                text: "select"
                onClicked: {
                    if(wasm_platform)
                    {
                        wasmFileDialog.open();
                    } else {
                        fileDialog.open();
                    }
                }
            }
            Text {
                text: apiServer.uploadPersent+"%";
                color: "red"
            }
        }

        FileDialog {
            id: fileDialog
            currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
            onAccepted: {
                img1.source = imagePath = selectedFile;
                apiServer.sendSample(imagePath);
            }
        }
    }
}

