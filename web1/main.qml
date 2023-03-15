import QtQuick
import QtQuick.Controls

Window {
    width: 940
    height: 680
    visible: true
    title: qsTr("Hello World")


    ScrollView{
        id: samplesBar;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 300;

        Row{
            anchors.fill: parent
            spacing: 16;

            ImageSelect{
                id: select1;
            }

            ImageSelect{
                id: select2;
            }

            ImageSelect{
                id: select3;
            }


        }
    }

    Row{
        anchors.top: samplesBar.bottom;

        Rectangle{
            width: target1.width
            height: target1.height
            border.width: 2;

            ImageSelect{
                id: target1

            }

        }

        Column{
            Text{
                text: "respons"
            }
            Button{
                text: "send"
                onClicked: {
                    var paths={};
                    paths["file1"]=select1.imagePath;
                    paths["file2"]=select2.imagePath;
                    paths["file3"]=select3.imagePath;
                    paths["file4"]=target1.imagePath;

                    ApiServer.api3(paths);
                }
            }
        }
    }


}
