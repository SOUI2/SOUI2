######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 23 19:27:34 2014
######################################################################

TEMPLATE = lib
TARGET = imgdecoder-png

!LIB_ALL:!COM_LIB{
	RC_FILE += imgdecoder-png.rc
	CONFIG += dll
}
else{
	CONFIG += staticlib
}

CONFIG(debug,debug|release){
	LIBS += zlibd.lib pngd.lib
}
else{
	LIBS += zlib.lib png.lib
}

DEPENDPATH += .
INCLUDEPATH += . \
			   ../../third-part/png \
			   ../../third-part/zlib \
			   ../../utilities/include \
			   ../../soui/include \

dir = ../..
include($$dir/common.pri)

# Input
HEADERS += imgdecoder-png.h decoder-apng.h
SOURCES += imgdecoder-png.cpp decoder-apng.cpp
