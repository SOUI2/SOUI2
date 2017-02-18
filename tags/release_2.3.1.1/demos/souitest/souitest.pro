######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 28 18:07:07 2014
######################################################################

TEMPLATE = app
TARGET = souitest

DEPENDPATH += .
INCLUDEPATH += . \
			   ../../utilities/include \
			   ../../soui/include \
			   ../../components \
			   ../../third-part/gtest/include \

dir = ../..
include($$dir/common.pri)

CONFIG(debug,debug|release){
	LIBS += utilitiesd.lib souid.lib gtestd.lib
}
else{
	LIBS += utilities.lib soui.lib gtest.lib
}

#指定生成的exe是基于控制台的
CONFIG += console

# Input
SOURCES += souitest.cpp


