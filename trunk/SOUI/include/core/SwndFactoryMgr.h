#pragma once
#include "core/ssingletonmap.h"


namespace SOUI
{
    class SWindow;

class SWindowFactory
{
public:
    virtual ~SWindowFactory() {}
    virtual SWindow* NewWindow() = 0;
    virtual LPCWSTR SWindowBaseName()=0;

    virtual const SStringW & getWindowType()=0;

    virtual SWindowFactory* Clone() const =0;
};

template <typename T>
class TplSWindowFactory : public SWindowFactory
{
public:
    //! Default constructor.
    TplSWindowFactory():m_strTypeName(T::GetClassName())
    {
    }

//     LPCWSTR DuiWindowName(){return T::GetClassName();}

    LPCWSTR SWindowBaseName(){return T::BaseClassName();}

    // Implement WindowFactory interface
    SWindow* NewWindow()
    {
        return new T;
    }

    virtual const SStringW & getWindowType()
    {
        return m_strTypeName;
    }

    virtual SWindowFactory* Clone() const 
    {
        return new TplSWindowFactory();
    }
protected:
    SStringW m_strTypeName;
};



typedef SWindowFactory* SWindowFactoryPtr;
class SOUI_EXP SWindowFactoryMgr :
    public SCmnMap<SWindowFactoryPtr,SStringW>
{
public:
    SWindowFactoryMgr(void);

    //************************************
    // Method:    RegisterFactory,ע��APP�Զ���Ĵ�����
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
    // Access:    public
    // Returns:   bool
    // Qualifier:
    // Parameter: SWindowFactory * pWndFactory
    //************************************
    bool UnregisterWndFactory(const SStringW & strClassType)
    {
        return  RemoveKeyObject(strClassType);
    }

    SWindow *CreateWindowByName(LPCWSTR pszClassName);

    LPCWSTR BaseClassNameFromClassName(LPCWSTR pszClassName);
protected:
    static void OnWndFactoryRemoved(const SWindowFactoryPtr & obj);

    void AddStandardWindowFactory();
};

}//namespace SOUI