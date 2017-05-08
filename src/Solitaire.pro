#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T14:49:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -DBUILDGUI

SOURCES += main/main.cpp\
        gui/g_board.cpp \
    game/Board.cpp \
    game/Card_stack.cpp \
    game/Console.cpp \
    game/Single_color_stack.cpp \
    game/Working_stack.cpp \
    gui/g_card.cpp \
    game/g_stack.cpp \
    gui/main_window.cpp

HEADERS  += gui/g_board.hpp \
    game/Board.hpp \
    game/Card.hpp \
    game/Card_deck_hidden.hpp \
    game/Card_deck_visible.hpp \
    game/Card_stack.hpp \
    game/Console.hpp \
    game/History.hpp \
    game/Move.hpp \
    game/Single_color_stack.hpp \
    game/Working_stack.hpp \
    gui/g_card.hpp \
    gui/g_stack.hpp \
    gui/globals.hpp \
    gui/main_window.hpp

DISTFILES += \
    ../lib/cards/back.png \
    ../lib/cards/C1.png \
    ../lib/cards/C10.png \
    ../lib/cards/C11.png \
    ../lib/cards/C12.png \
    ../lib/cards/C13.png \
    ../lib/cards/C2.png \
    ../lib/cards/C3.png \
    ../lib/cards/C4.png \
    ../lib/cards/C5.png \
    ../lib/cards/C6.png \
    ../lib/cards/C7.png \
    ../lib/cards/C8.png \
    ../lib/cards/C9.png \
    ../lib/cards/D1.png \
    ../lib/cards/D10.png \
    ../lib/cards/D11.png \
    ../lib/cards/D12.png \
    ../lib/cards/D13.png \
    ../lib/cards/D2.png \
    ../lib/cards/D3.png \
    ../lib/cards/D4.png \
    ../lib/cards/D5.png \
    ../lib/cards/D6.png \
    ../lib/cards/D7.png \
    ../lib/cards/D8.png \
    ../lib/cards/D9.png \
    ../lib/cards/empty.png \
    ../lib/cards/H1.png \
    ../lib/cards/H10.png \
    ../lib/cards/H11.png \
    ../lib/cards/H12.png \
    ../lib/cards/H13.png \
    ../lib/cards/H2.png \
    ../lib/cards/H3.png \
    ../lib/cards/H4.png \
    ../lib/cards/H5.png \
    ../lib/cards/H6.png \
    ../lib/cards/H7.png \
    ../lib/cards/H8.png \
    ../lib/cards/H9.png \
    ../lib/cards/S1.png \
    ../lib/cards/S10.png \
    ../lib/cards/S11.png \
    ../lib/cards/S12.png \
    ../lib/cards/S13.png \
    ../lib/cards/S2.png \
    ../lib/cards/S3.png \
    ../lib/cards/S4.png \
    ../lib/cards/S5.png \
    ../lib/cards/S6.png \
    ../lib/cards/S7.png \
    ../lib/cards/S8.png \
    ../lib/cards/S9.png
