#pragma once
#include "duisingletonmap.h"


namespace SOUI
{
    class SWindow;

class SWindowFactory
{
public:
    virtual ~SWindowFactory() {}
    virtual SWindow* NewWindow() = 0;
    virtual LPCSTR DuiWindowBaseName()=0;

    virtual const CDuiStringA & getWindowType()=0;

    virtual SWindowFactory* Clone() const =0;
};

template <typename T>
class TplDuiWindowFactory : public SWindowFactory
{
public:
    //! Default constructor.
    TplDuiWindowFactory():m_strTypeName(T::GetClassName())
    {
    }

    LPCSTR DuiWindowName(){return T::GetClassName();}

    LPCSTR DuiWindowBaseName(){return T::BaseClassName();}

    // Implement WindowFactory interface
    SWindow* NewWindow()
    {
        return new T;
    }

    virtual const CDuiStringA & getWindowType()
    {
        return m_strTypeName;
    }

    virtual SWindowFactory* Clone() const 
    {
        return new TplDuiWindowFactory();
    }
protected:
    CDuiStringA m_strTypeName;
};



typedef SWindowFactory* SWindowFactoryPtr;
class SOUI_EXP DuiWindowFactoryMgr :
    public DuiCmnMap<SWindowFactoryPtr,CDuiStringA>
{
public:
    DuiWindowFactoryMgr(void);

    //************************************
    // Method:    RegisterFactory,ע��APP�Զ���Ĵ�����
    // FullName:  SOUI::DuiWindowFactoryManager::RegisterFactory
    // Access:    public
    // Returns:   bool
    // Qualifier:
    // Parameter: SWindowFactory * pWndFactory:���ڹ���ָ��
    // Parameter: bool bReplace:ǿ���滻ԭ�й�����־
    //************************************
    bool RegisterWndFactory(SWindowFactory & wndFactory,bool bReplace=false)
    {
        if(HasKey(wndFactory.getWindowType()))
        {
            if(!bReplace) return false;
            RemoveKeyObject(wndFactory.getWindowType());
        }
        AddKeyObject(wndFactory.getWindowType(),wndFactory.Clone());
        return true;
    }

    //************************************
    // Method:    UnregisterFactor,��ע��APP�Զ���Ĵ�����
    // FullName:  SOUI::DuiWindowFactoryManager::UnregisterFactor
    // Access:    public
    // Returns:   bool
    // Qualifier:
    // Parameter: SWindowFactory * pWndFactory
    //************************************
    bool UnregisterWndFactory(const CDuiStringA & strClassType)
    {
        return  RemoveKeyObject(strClassType);
    }

    SWindow *CreateWindowByName(LPCSTR pszClassName);

    LPCSTR BaseClassNameFromClassName(LPCSTR pszClassName);
protected:
    static void OnWndFactoryRemoved(const SWindowFactoryPtr & obj);

    void AddStandardWindowFactory();
};

}//namespace SOUI