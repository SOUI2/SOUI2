// luaScriptModule.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <event/EventSubscriber.h>
#include "ScriptModule-Lua.h"
#include "../lua_tinker/lua_tinker.h"
#include <string/strcpcvt.h>

using namespace SOUI;

extern BOOL SOUI_Export_Lua(lua_State *L);

wchar_t * cast_a2w(char * str)
{
	return (wchar_t *)str;
}

int Utf8ToW(lua_State* L)
{
	size_t n = 0;
	char* str = (char*)luaL_checklstring(L, -1, &n);
	if(!str)   return 0;
	SStringW strW=S_CA2W(str,CP_UTF8);
	lua_pushlstring(L, (const char*)(LPCWSTR)strW, 2*strW.GetLength()+2);
	return 1;
}

class LuaFunctionSlot : public SlotFunctorBase
{
public:
	//! Slot function type.
	LuaFunctionSlot(lua_State *pLuaState,LPCSTR pszLuaFun) 
		: m_pLuaState(pLuaState)
		, m_luaFun(pszLuaFun)
	  {}

	  virtual bool operator()(EventArgs *pArg)
	  {
		  return lua_tinker::call<bool>(m_pLuaState,m_luaFun,pArg);
	  }

	  virtual SlotFunctorBase* Clone() const 
	  {
		  return new LuaFunctionSlot(m_pLuaState,m_luaFun);
	  }

	  virtual bool Equal(const SlotFunctorBase & sour)const 
	  {
		  if(sour.GetSlotType()!=GetSlotType()) return false;
		  const LuaFunctionSlot *psour=static_cast<const LuaFunctionSlot*>(&sour);
		  ASSERT(psour);
		  return psour->m_luaFun==m_luaFun && psour->m_pLuaState==m_pLuaState;
	  }

	  virtual UINT GetSlotType() const {return SLOT_USER+1;}

private:
	SStringA m_luaFun;
	lua_State *m_pLuaState;
};


SScriptModule_Lua::SScriptModule_Lua()
{
	d_state = lua_open();
	if(d_state)
	{
		luaL_openlibs(d_state);
		SOUI_Export_Lua(d_state);
		lua_register(d_state, "A2W", Utf8ToW);
		lua_tinker::def(d_state, "cast_a2w", cast_a2w);
		luaL_dostring(d_state,"function L (str)\n return cast_a2w(A2W(str));\nend");//ע��һ��ȫ�ֵ�"L"������������utf8������ַ���ת��Ϊ���ַ�
	}
}


SScriptModule_Lua::~SScriptModule_Lua()
{
	if (d_state)
	{
		lua_close( d_state );
	}
}


LPCSTR SScriptModule_Lua::getIdentifierString() const
{
	return "SOUI.Script.Lua5.1";
}

void SScriptModule_Lua::executeScriptFile( LPCSTR pszScriptFile )
{
 	lua_tinker::dofile(d_state,pszScriptFile);
}

bool SScriptModule_Lua::executeScriptedEventHandler( LPCSTR handler_name, EventArgs *pArg)
{
	LuaFunctionSlot luaFunSlot(d_state,handler_name);
	return luaFunSlot(pArg);
}

void SScriptModule_Lua::executeString( LPCSTR str )
{
	lua_tinker::dostring(d_state,str);
}

bool SScriptModule_Lua::subscribeEvent(SOUI::SWindow* target, UINT uEvent, LPCSTR subscriber_name )
{
	return target->subscribeEvent(uEvent,LuaFunctionSlot(d_state,subscriber_name));
}

bool SScriptModule_Lua::unsubscribeEvent(SOUI::SWindow* target, UINT uEvent, LPCSTR subscriber_name )
{
	return target->unsubscribeEvent(uEvent,LuaFunctionSlot(d_state,subscriber_name));
}


//////////////////////////////////////////////////////////////////////////
BOOL SCreateInstance(IObjRef ** ppScript)
{
    *ppScript= new SScriptModule_Lua;
    return TRUE;
}
