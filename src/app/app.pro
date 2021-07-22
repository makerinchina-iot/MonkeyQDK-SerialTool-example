include(../../MonkeyQDK.pri)

QT += core gui widgets

TEMPLATE = app

TARGET = MonkeySerialExample

LIBS += -L$$APP_LIBS_PATH

LIBS += \
    -lutils \
    -lextensionsystem \
    -lcoreplugin \

SOURCES += \
    main.cpp

DESTDIR = $$APP_OUT_PATH

#icon
RC_FILE += app_icon.rc
