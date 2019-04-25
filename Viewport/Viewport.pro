#-------------------------------------------------
#
# Project created by QtCreator 2016-01-21T09:39:33
#
#-------------------------------------------------

QT      += core gui
QT      += quick
QT      += testlib
CONFIG  += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Viewport
TEMPLATE = app


SOURCES +=\
    QSFMLCanvas.cpp \
    WriteAction.cpp \
    SeasonalGrowback.cpp \
    ReadAction.cpp \
    PollutionFormation.cpp \
    Location.cpp \
    IterativeWriteAction.cpp \
    Inheritance.cpp \
    IndependentAction.cpp \
    Growback.cpp \
    group.cpp \
    GarbageCollection.cpp \
    Diffusion.cpp \
    AgentReplacement.cpp \
    AgentMove.cpp \
    AgentMetabolism.cpp \
    AgentMating.cpp \
    AgentLoanPayments.cpp \
    AgentDisease.cpp \
    AgentDeath.cpp \
    AgentCulture.cpp \
    AgentCredit.cpp \
    AgentCombat.cpp \
    AgentBasicMove.cpp \
    Agent.cpp \
    Action.cpp \
    World.cpp \
    ViewPort.cpp \
    Sugarscape.cpp \
    main.cpp \
    ControlWidget.cpp \
    qcustomplot.cpp \
    GraphPort.cpp \
    qcpdocumentobject.cpp \
    ControlWidgetSlim.cpp


HEADERS  += \
    QSFMLCanvas.h \
    SeasonalGrowback.h \
    ReadAction.h \
    PollutionFormation.h \
    Location.h \
    IterativeWriteAction.h \
    Inheritance.h \
    IndependentAction.h \
    Growback.h \
    group.h \
    GarbageCollection.h \
    Diffusion.h \
    AgentReplacement.h \
    AgentMove.h \
    AgentMetabolism.h \
    AgentMating.h \
    AgentLoanPayments.h \
    AgentDisease.h \
    AgentDeath.h \
    AgentCulture.h \
    AgentCredit.h \
    AgentCombat.h \
    AgentBasicMove.h \
    Agent.h \
    Action.h \
    WriteAction.h \
    ViewPort.h \
    World.h \
    ControlWidget.h \
    qcustomplot.h \
    GraphPort.h \
    qcpdocumentobject.h \
    ControlWidgetSlim.h

FORMS    += \
    ControlWidget.ui \
    GraphPort.ui \
    ControlWidgetSlim.ui

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

# Mac Setup

# INCLUDEPATH += /usr/local/include
# LIBS += -L/usr/local/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


# End Mac Setup

DISTFILES += \
    config.ini
