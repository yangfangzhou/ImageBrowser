#include "client.h"

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);
    return imglistBrowse.at(id.toInt());
}

flashImage::flashImage(QObject *parent):QObject(parent)
{
}

void flashImage::reflashImage(int picindex)
{
    QMutexLocker locker(&mutex);
    qWarning() << picindex << ShowImageIns->qmlimglistnum();

    int shouldShowlistNum;
    if (ShowImageIns->qmlimglistnum() > (picindex * 4 + 36))
    {
        if(picindex >= 0){
            shouldShowlistNum = picindex * 4 + 36;
        } else {
            shouldShowlistNum = 35;
        }
    } else {
        shouldShowlistNum = ShowImageIns->qmlimglistnum();
    }
    int flashIndex = ((picindex * 4 + 36) < shouldShowlistNum ? (picindex * 4): (shouldShowlistNum -36));
    int i = flashIndex;
    if(flashIndex > 0){
        int j = 0;
        for (;j<flashIndex;j++){
            if(ShowImageIns->m_pImgProvider->imglistBrowse.at(j) != ShowImageIns->imgTmpload){
                ShowImageIns->m_pImgProvider->imglistBrowse.replace(j,ShowImageIns->imgTmpload);
            }
        }
    }
    for (;shouldShowlistNum < ShowImageIns->qmlimglistnum();shouldShowlistNum++){
        if(ShowImageIns->m_pImgProvider->imglistBrowse.at(shouldShowlistNum) != ShowImageIns->imgTmpload){
            ShowImageIns->m_pImgProvider->imglistBrowse.replace(shouldShowlistNum,ShowImageIns->imgTmpload);
        }
    }
    for (;i< flashIndex + 36;i++){
        if(ShowImageIns->m_pImgProvider->imglistBrowse.at(i) == ShowImageIns->imgTmpload){
            imgTmp.load(ShowImageIns->currentInfo.at(i).absoluteFilePath());
            ShowImageIns->m_pImgProvider->imglistBrowse.replace(i,imgTmp);
        }
    }
}

IMPLEMENT_SINGLETON(ShowImage)

ShowImage::ShowImage()
{
    imgTmpload.load(QString(":/pic_loading.png"));
    QDir currentInfoDir("./media/sdcard/");
    QStringList fileList;
    fileList<<"*.jpg" << "*.png";
    currentInfo = currentInfoDir.entryInfoList(fileList,QDir::Files);
    m_loadTotalNum =  currentInfo.count();

    m_pImgProvider = new ImageProvider();
    m_flashImage = new flashImage();
    pImgProviderThread = new QThread();
    if(NULL != pImgProviderThread){
        m_flashImage->moveToThread(pImgProviderThread);
        pImgProviderThread->start();
        connect(this,SIGNAL(getPicindex(int)),m_flashImage,SLOT(reflashImage(int)),Qt::QueuedConnection);
    }
    getPicFileList();
}

QQuickImageProvider *ShowImage::imageprovideRe()
{
    return m_pImgProvider;
}

void ShowImage::getPicFileList(){
    m_pImgProvider->imglistBrowse.clear();
    for (int i = 0;i<qmlimglistnum();i++){
        m_pImgProvider->imglistBrowse.append(imgTmpload);
    }
}

int ShowImage::qmlimglistnum()
{
    return m_loadTotalNum;
}

void ShowImage::setPicindex(int index)
{
    emit getPicindex(index);
}

