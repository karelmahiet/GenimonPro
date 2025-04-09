TEMPLATE = vcapp
TARGET = Genimon
CONFIG += warn_on qt debug windows console
SOURCES +=\
    main.cpp \
    controle.cpp \
    capture.cpp \
    choixaction.cpp \
    choixjoueur.cpp \
    combat.cpp \
    commande.cpp \
    genidex.cpp \
    genimon.cpp \
    historencontre.cpp \
    map.cpp \
    regle.cpp \
    pause.cpp \
    mainmenu.cpp
HEADERS += \
    controle.h \
    capture.h \
    choixaction.h \
    choixjoueur.h \
    combat.h \
    commande.h \
    genidex.h \
    genimon.h \
    historencontre.h \
    json.hpp \
    SerialPort.hpp \
    unistd.h \
    map.h \
    regle.h \
    pause.h \
    mainmenu.h

FORMS += \
    controle.ui \
    capture.ui \
    choixaction.ui \
    choixjoueur.ui \
    combat.ui \
    commande.ui \
    genidex.ui \
    historencontre.ui \
    map.ui \
    regle.ui \
    pause.ui \
    mainmenu.ui

RESOURCES += \
    Image.qrc \
    Music.qrc \

QT += widgets multimedia serialport