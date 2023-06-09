QT += quick

wasm{
QT += widgets
}

HEADERS += \
    ApiServer.h \
    ServerConn/sendrequest.h \
    ServerConn/serverconn.h \
    WasmFileDialog.h

SOURCES += \
    ApiServer.cpp \
    ServerConn/sendrequest.cpp \
    ServerConn/serverconn.cpp \
    WasmFileDialog.cpp \
        main.cpp


RESOURCES += qml.qrc

resources.files = main.qml \
                  ImageSelect.qml \
                  TargetImage.qml
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    ImageSelect.qml
