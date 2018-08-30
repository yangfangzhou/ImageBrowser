#ifndef IMG_H
#define IMG_H
#include <QQuickImageProvider>
#include <QImage>
#include <QBuffer>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QThread>
#include <QDebug>
#include <QImageReader>
#include <QMutexLocker>
#include "singleton.h"

#define ShowImageIns ShowImage::Instance()

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    QList<QImage> imglistBrowse;
};

class flashImage : public QObject
{
    Q_OBJECT
public:
    explicit flashImage(QObject *parent = 0);
    QImage imgTmp;
public slots:
    void reflashImage(int picindex);
private:
    QMutex mutex;
};

class ShowImage : public QObject
{
    Q_OBJECT
protected:
    ShowImage();
    static  ShowImage* m_pInstance;
public:
    static  ShowImage* Instance();
    QImage imgTmpload;
    ImageProvider *m_pImgProvider;
    QQuickImageProvider * imageprovideRe();
    flashImage *m_flashImage;
    QThread *pImgProviderThread;
    int currentPicIndex;
    QFileInfoList currentInfo;
    QImageReader reader;
public slots:
    void getPicFileList();
    int qmlimglistnum();
    void setPicindex(int index);

signals:
    void callQmlRefeshImg();
    void picindexChanged();
    void getPicindex(int index);
private:
    int m_loadTotalNum;
    int m_picindex;
};
#endif // IMG_H
