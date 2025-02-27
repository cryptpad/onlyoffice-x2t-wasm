QT -= core
QT -= gui

VERSION = 0.0.0.1
TARGET = Fb2File
TEMPLATE = lib

CONFIG += shared
CONFIG += plugin

DEFINES += FB2FILE_USE_DYNAMIC_LIBRARY

CORE_ROOT_DIR = $$PWD/..
PWD_ROOT_DIR = $$PWD
include($$CORE_ROOT_DIR/Common/base.pri)

include($$CORE_ROOT_DIR/Common/3dParty/html/gumbo.pri)

# CryptPad: UnicodeConverter is linked in a later step. Do not link here.
# ADD_DEPENDENCY(kernel, UnicodeConverter, graphics)
ADD_DEPENDENCY(kernel, graphics)

CONFIG += core_boost_regex
include($$CORE_ROOT_DIR/Common/3dParty/boost/boost.pri)

SOURCES += Fb2File.cpp

HEADERS += Fb2File.h
HEADERS += template/template.h
