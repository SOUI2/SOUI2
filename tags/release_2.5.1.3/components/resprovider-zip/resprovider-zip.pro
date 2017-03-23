######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 23 19:28:51 2014
######################################################################

TEMPLATE = lib
TARGET =  resprovider-zip

!LIB_ALL:!COM_LIB{
	RC_FILE += ResProvider-Zip.rc
	CONFIG += dll
}
else{
	CONFIG += staticlib
}

DEPENDPATH += .
INCLUDEPATH += . \
			   ../../third-part/zlib \
			   ../../soui/include \
			   ../../utilities/include \

DEFINES += RESPROVIDERZIP_EXPORTS

dir = ../..
include($$dir/common.pri)

CONFIG(debug,debug|release){
	LIBS += zlibd.lib utilitiesd.lib
}
else{
	LIBS += zlib.lib utilities.lib
}


PRECOMPILED_HEADER = stdafx.h

# Input
HEADERS += SResProviderZip.h ZipArchive.h
SOURCES += cursoricon.cpp \
           SResProviderZip.cpp \
           zipArchive.cpp
