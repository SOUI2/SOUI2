TEMPLATE = subdirs
TARGET = third-part
DEPENDPATH += .
INCLUDEPATH += .

include(../cpy-cfg.pri)

SUBDIRS += gtest
SUBDIRS += png
SUBDIRS += skia
SUBDIRS += zlib
SUBDIRS += lua-52
SUBDIRS += smiley
SUBDIRS += mhook

CONFIG(c++11){
#7z��Ҫc11֧��
	SUBDIRS += 7z
}
