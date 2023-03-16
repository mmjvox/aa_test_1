import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import ApiServer
import WasmFileDialog

Row{
    anchors.top: samplesBar.bottom;

    property string imagePath:"";

    Rectangle{
        width: childrenRect.width;
        height: childrenRect.height;
        border.width: 1;
        border.color: "red";

        WasmFileDialog{
            id: wasmFileDialog;
            onAccepted: (selectedFile)=>{
                img1.source = imagePath = selectedFile;
                apiServer.sendTarget(selectedFile);
            }
        }

        ApiServer{
            id: apiServer;
            onServerCalc: (value)=>{ respText.text = value }
        }

        DropArea{
            anchors.fill: parent;

            onDropped: (drop)=>{
                img1.source = imagePath = drop.text;
                apiServer.sendTarget(imagePath);
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
                    apiServer.sendTarget(imagePath);
                }
            }
        }
    }

    Column{
        Text{
            id: respText;
            text: "respons"
        }
        Button{
            text: "send"
            onClicked: {
                apiServer.requestCalc();
            }
        }
    }
}
