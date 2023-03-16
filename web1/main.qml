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


    TargetImage{}


}
