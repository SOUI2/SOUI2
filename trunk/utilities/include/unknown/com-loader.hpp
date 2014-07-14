#pragma once

//�������������
//�����Ҫ�ṩSCreateInstance�ӿڡ��ӿڶ��������funSCreateInstance
class SComLoader
{
    typedef BOOL (*funSCreateInstance)(IObjRef **);
public:
    SComLoader():m_hMod(0),m_funCreateInst(NULL){}
    ~SComLoader()
    {
        if(m_hMod) FreeLibrary(m_hMod);
    }

    BOOL CreateInstance(LPCTSTR pszDllPath,IObjRef **ppObj)
    {
        if(!m_funCreateInst)
        {
            m_hMod=LoadLibrary(pszDllPath);
            if(!m_hMod) return FALSE;
            m_funCreateInst=(funSCreateInstance)GetProcAddress(m_hMod,"SCreateInstance");
            if(!m_funCreateInst)
            {
                FreeLibrary(m_hMod);
                return FALSE;
            }
        }
        return m_funCreateInst(ppObj);
    }
protected:
    HMODULE m_hMod;
    funSCreateInstance m_funCreateInst;
};