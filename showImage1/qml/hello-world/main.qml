import QtQuick 2.0

Item {
    visible: true
    width: 1024
    height: 600
    //    color: "black"

    GridView {
        id: preview
        x: 25
        y: 25
        width: 1004
        height: 510
        model: pcimod
        clip: true
        cellWidth: 244
        cellHeight: 170
        snapMode: GridView.SnapToRow
        //        highlight: Rectangle { width: 80; height: 80; color: "lightsteelblue" }
        //        focus: true

        delegate: Image
        {
            id:img
            width: 240
            height: 168
            cache: false
            //                asynchronous : true           //1of4
            //            property string gridindex
            source: "image://CodeImg/" + gridindex

            MouseArea {
                anchors.fill: parent

                //                    acceptedButtons: Qt.MidButton
                onWheel: {
                    if (wheel.angleDelta.y > 0 && parent.GridView.view.currentIndex < (parent.GridView.view.count -1)){
                        parent.GridView.view.currentIndex +=1
                    }
                    if (wheel.angleDelta.y < 0 && parent.GridView.view.currentIndex > (0)){
                        parent.GridView.view.currentIndex -=1
                    }
                }
                onClicked: {
                    preview.visible = false
                    imgCurrent.visible = true
                    imgCurrent.source = "image://CodeImg/" + gridindex
                }
            }
        }
        onContentYChanged: {
            showtimer.running = true
        }
    }

    ListModel {
        id: pcimod
    }
    Image
    {
        id: imgCurrent
        x: 10
        y: 10
        width: 1024
        height: 600
        visible: false
        cache: false
        source: "image://CodeImg/1"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                preview.visible = true
                imgCurrent.visible = false
            }
        }
    }

    Image {
        id: prebutton
        anchors.verticalCenter: imgCurrent.verticalCenter
        visible: imgCurrent.visible
        source: "qrc:/image_last_P.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (imgCurrent.source.toString().substring(imgCurrent.source.toString().lastIndexOf("/")+1) > 0){

                    imgCurrent.source = "image://CodeImg/" + (imgCurrent.source.toString().substring(imgCurrent.source.toString().lastIndexOf("/")+1) - 1)
                }
            }
        }
    }
    Image {
        id: nextbutton
        anchors.verticalCenter: imgCurrent.verticalCenter
        anchors.right: imgCurrent.right
        visible: imgCurrent.visible
        source: "qrc:/image_next_P.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (Number(imgCurrent.source.toString().substring(imgCurrent.source.toString().lastIndexOf("/")+1)) < CodeImage.qmlimglistnum() -1 ){
                    imgCurrent.source = "image://CodeImg/" + (Number(imgCurrent.source.toString().substring(imgCurrent.source.toString().lastIndexOf("/")+1))+1)
                }
            }
        }
    }

    Connections{
        target: CodeImage;
        onCallQmlRefeshImg: {
            //        console.log("CodeImage.qmlimglistnum(); "+CodeImage.qmlimglistnum())
            pcimod.clear();
            for (var i = 0;i< CodeImage.qmlimglistnum();i++){
                pcimod.append({"gridindex":i.toString()});
            }
        }
    }
    property int picIndexNow: (preview.contentY /170).toFixed(0) >=0 ? (preview.contentY /170).toFixed(0) : 0

    Timer{
        id: showtimer
        running: true
        repeat: true
        interval:  200
        onTriggered: {
            if(!preview.moving){
                CodeImage.setPicindex(picIndexNow);
            }
            showtimer.running = false
        }
    }
    Timer{
        id: showtimer2
        running: true
        repeat: true
        interval:  200
        onTriggered: {
            if(!preview.moving){
                var indexi;
                if(picIndexNow * 4 > CodeImage.qmlimglistnum() -36){
                    indexi = CodeImage.qmlimglistnum() -36;
                } else {
                    indexi = picIndexNow *4
                }
                for (var j = indexi;j<indexi +36;j++){
//                    console.log(pcimod.get(j).gridindex)
                    pcimod.setProperty(j,"gridindex","")
                    pcimod.setProperty(j,"gridindex",j.toString())
                }
            }
        }
    }
}
