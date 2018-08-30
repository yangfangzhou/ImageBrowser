#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWidgets/QApplication>
#include <QScreen>
#include <QtWidgets/QWidget>
#include <QImage>
#include "client.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    ShowImage *CodeImage= ShowImageIns->Instance();
    viewer.rootContext()->setContextProperty("CodeImage",CodeImage);
    viewer.engine()->addImageProvider(QLatin1String("CodeImg"),CodeImage->m_pImgProvider);
    viewer.setSource(QStringLiteral("qrc:/qml/hello-world/main.qml"));
    viewer.showExpanded();
    emit ShowImageIns->callQmlRefeshImg();

    return app.exec();
}
