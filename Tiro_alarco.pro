QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Tiro_alarco
TEMPLATE = app

INCLUDEPATH += include

HEADERS += \
    include/Flecha.h \
    include/Jugador.h \
    include/MainWindow.h \
    include/Medidor.h \
    include/Objetivo.h \
    include/ObjetivoFijo.h \
    include/ObjetivoMovil.h \
    include/Portal.h \
    include/Nivel.h \
    include/MainWindow.h

SOURCES += \
    main.cpp \
    src/Flecha.cpp \
    src/Jugador.cpp \
    src/MainWindow.cpp \
    src/Medidor.cpp \
    src/Objetivo.cpp \
    src/ObjetivoFijo.cpp \
    src/ObjetivoMovil.cpp \
    src/Portal.cpp \
    src/Nivel.cpp \
    src/MainWindow.cpp

RESOURCES += \
    assets.qrc
