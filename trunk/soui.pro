TEMPLATE = subdirs
TARGET = soui
DEPENDPATH += .
INCLUDEPATH += .


SUBDIRS += utilities
SUBDIRS += soui
SUBDIRS += components/imgdecoder-wic
SUBDIRS += components/render-gdi
SUBDIRS += components/myskia
SUBDIRS += components/render-skia
SUBDIRS += components/translator
SUBDIRS += components/zlib
SUBDIRS += components/resprovider-zip
CONFIG(DLL_SOUI){
	#ֻ�ڲ���DLL��ʽ����SOUIʱ֧��LUA
	SUBDIRS += components/ScriptModule-LUA/lua-51
	SUBDIRS += components/ScriptModule-LUA/ScriptModule
}
SUBDIRS += demo
