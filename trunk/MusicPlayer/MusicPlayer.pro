######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 21 17:00:01 2014
######################################################################

TEMPLATE = app
TARGET = MusicPlayer
DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += . \
			   ../utilities/include \
			   ../soui/include \
			   ../components \
			   ../third-part/bass 
			   
dir = ..
include($$dir/common.pri)

QMAKE_LIBDIR += ../third-part/bass

CONFIG(debug,debug|release){
	LIBS += utilitiesd.lib souid.lib
}
else{
	LIBS += utilities.lib soui.lib
}
LIBS += bass.lib

PRECOMPILED_HEADER = stdafx.h

# Input
HEADERS += MainDlg.h \
           resource.h \
		   BassMusic.h \
			DropEx.h \
			Macro.h \
			MusicOperat.h \
           ../controls.extend/STurn3DView.h \
           ../controls.extend/image3d/3dlib.h \
           ../controls.extend/image3d/3dmatrix.h \
           ../controls.extend/image3d/3dTransform.h \
           ../controls.extend/image3d/PerspectiveTransform.h \
		   ../controls.extend/trayicon/SShellNotifyIcon.h \
		   ../controls.extend/sflywnd.h

SOURCES += MainDlg.cpp \
           BassMusic.cpp \
		   MusicPlayer.cpp \
		   MusicOperat.cpp \
           ../controls.extend/STurn3DView.cpp \
           ../controls.extend/image3d/3dlib.cpp \
           ../controls.extend/image3d/3dmatrix.cpp \
           ../controls.extend/image3d/3dtransform.cpp \
 		   ../controls.extend/trayicon/SShellNotifyIcon.cpp \
		   ../controls.extend/sflywnd.cpp
          
RC_FILE += musicplayer.rc
