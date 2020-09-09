QT += core gui sql widgets

CONFIG += c++11

TARGET = Hospital
TEMPLATE = app

# The following define makes your compiler emit warnings if you use any feature of Qt
# which has been marked as deprecated. Please consult the documentation in order to know how fix it.
DEFINES += QT_DEPRECATED_WARNINGS

# Generate make file only for certain build type
CONFIG -= debug_and_release

# Set app version
REV = $$system(git rev-list --count HEAD)
BUILD_VERSION = 0.1.0.$$REV
VERSION = $$BUILD_VERSION

# Add include path (simplify include in the source files)
INCLUDEPATH += \
    $$PWD/sources/

PRECOMPILED_HEADER = sources/precompiled.h

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp

HEADERS += \
    sources/mainwindow.h \
    sources/precompiled.h

FORMS += \
    forms/mainwindow.ui

TRANSLATIONS += \
    resources/translations/hospital_ru.ts

RESOURCES += \
    resources/resources.qrc

win32: PLATFORM = "windows"
linux: PLATFORM = "linux"
macx:  PLATFORM = "mac"

CONFIG( debug, debug|release ) {
    # Debug
    BUILD_CONFIG = "debug"
} else {
    # Release
    BUILD_CONFIG = "release"
}

DESTDIR = $$PWD/bin/$${PLATFORM}_$${BUILD_CONFIG}/

# Generate translations
system("lupdate -no-obsolete -locations none $$shell_path($$PWD/hospital.pro)" & \
                               lrelease $$TRANSLATIONS )

# Deployment
win32 {
    DEPLOY_TARGET = $$shell_quote($$DESTDIR/$${TARGET}.exe)
    DEPLOY_COMMAND = windeployqt --no-compiler-runtime --no-opengl-sw
    RC_ICONS = ./resources/appicon/hospital.ico
    QMAKE_TARGET_COMPANY = NixSolutions LLC
    QMAKE_TARGET_PRODUCT = Hospital Management App
    QMAKE_TARGET_DESCRIPTION = Hospital Data Management
    QMAKE_TARGET_COPYRIGHT = "NixSolutions LLC \\251 2020"
}

macx {
    DEPLOY_TARGET = $$shell_quote($$DESTDIR/$${TARGET}.app)
    DEPLOY_COMMAND = macdeployqt
    ICON = ./resources/appicon/hospital.icns
    #QMAKE_INFO_PLIST=./resources/hospital.plist
}

win32|macx {
    # Generate release
    CONFIG(release, debug|release): QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
}

Copy_DB.commands = \
   $(COPY_DIR) $$shell_path($$PWD/resources/*.db) \
               $$shell_path($$DESTDIR)
QMAKE_EXTRA_TARGETS += Copy_DB
POST_TARGETDEPS += Copy_DB


