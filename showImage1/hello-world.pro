# Add more folders to ship with the application, here
#folder_01.source = qml/hello-world
#folder_01.target = qml
#DEPLOYMENTFOLDERS = folder_01
TEMPLATE = app
TARGET = showImage
QT += qml quick
CONFIG += qtquickcompiler

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    client.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    qtsource.qrc

HEADERS += \
    singleton.h \
    client.h
#DEFINES += QT_NO_WARNING_OUTPUT \
#QT_NO_DEBUG_OUTPUT
