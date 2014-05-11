#pragma once
#include "DuiSkinBase.h"

namespace SOUI
{

	class CSkinFactory
	{
	public:
		virtual ~CSkinFactory() {}
		virtual CDuiSkinBase * NewSkin()=NULL;
		virtual const CDuiStringA & GetTypeName()=NULL;
		virtual CSkinFactory * Clone()=NULL;
	};

	template<typename T>
	class TplSkinFactory :public CSkinFactory
	{
	public:
		TplSkinFactory():m_strTypeName(T::GetClassName())
		{
		}

		virtual CDuiSkinBase * NewSkin()
		{
			return new T;
		}

		virtual const CDuiStringA & GetTypeName()
		{
			return m_strTypeName;
		}

		virtual CSkinFactory * Clone()
		{
			return new TplSkinFactory<T>;
		}
	protected:
		CDuiStringA m_strTypeName;
	};

	typedef CSkinFactory * CSkinFactoryPtr;
	class SOUI_EXP DuiSkinFactoryManager: public DuiCmnMap<CSkinFactoryPtr,CDuiStringA>
	{
	public:
		DuiSkinFactoryManager()
		{
			m_pFunOnKeyRemoved=OnSkinRemoved;
			AddStandardSkin();
		}

		bool RegisterSkinFactory(CSkinFactory &skinFactory,bool bReplace=false)
		{
			if(HasKey(skinFactory.GetTypeName()))
			{
				if(!bReplace) return false;
				RemoveKeyObject(skinFactory.GetTypeName());
			}
			AddKeyObject(skinFactory.GetTypeName(),skinFactory.Clone());
			return true;
		}

		bool UnregisterSkinFactory(const CDuiStringA & strClassName)
		{
			return RemoveKeyObject(strClassName);
		}

		CDuiSkinBase * CreateSkinByName(LPCSTR pszClassName);

	protected:
		static void OnSkinRemoved(const CSkinFactoryPtr & obj);
		void AddStandardSkin();
	};
}//end of namespace