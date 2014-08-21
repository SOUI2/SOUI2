TEMPLATE = subdirs
TARGET = soui
DEPENDPATH += .
INCLUDEPATH += .

SUBDIRS += utilities
SUBDIRS += soui
SUBDIRS += soui-sys-resource
SUBDIRS += components/imgdecoder-wic
SUBDIRS += components/render-gdi
SUBDIRS += components/myskia
SUBDIRS += components/freetype
SUBDIRS += components/render-skia
SUBDIRS += components/translator
SUBDIRS += components/zlib
SUBDIRS += components/resprovider-zip
DLL_SOUI{
	SUBDIRS += components/ScriptModule-LUA/lua-51
	SUBDIRS += components/ScriptModule-LUA/ScriptModule
}
SUBDIRS += demo
SUBDIRS += qqlogin
