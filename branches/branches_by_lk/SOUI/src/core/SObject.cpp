#include "souistd.h"
#include "core/sobject.h"
#include "res.mgr/SObjDefAttr.h"

namespace SOUI
{
    BOOL SObject::InitFromXml( pugi::xml_node xmlNode )
    {
        if(!xmlNode) return FALSE;
#ifdef _DEBUG
        {
            pugi::xml_writer_buff writer;
            xmlNode.print(writer,L"\t",pugi::format_default,pugi::encoding_utf16);
            m_strXml=SStringW(writer.buffer(),writer.size());
        }
#endif

        //�������������Ĭ������
        pugi::xml_node defAttr = GETCSS(GetObjectClass());
        if(defAttr)
        {
            //���ȴ���"class"����
            pugi::xml_attribute attrClass=defAttr.attribute(L"class");
            if(attrClass)
            {
                attrClass.set_userdata(1);
                SetAttribute(attrClass.name(), attrClass.value(), TRUE);
            }
            for (pugi::xml_attribute attr = defAttr.first_attribute(); attr; attr = attr.next_attribute())
            {
                if(attr.get_userdata()) continue;
                SetAttribute(attr.name(), attr.value(), TRUE);
            }
            if(attrClass)
            {
                attrClass.set_userdata(0);
            }
        }

        //���õ�ǰ���������

        //���ȴ���"class"����
        pugi::xml_attribute attrClass=xmlNode.attribute(L"class");
        if(attrClass)
        {
            attrClass.set_userdata(1);      //Ԥ����������ԣ�����������һ��userdata
            SetAttribute(attrClass.name(), attrClass.value(), TRUE);
        }
        for (pugi::xml_attribute attr = xmlNode.first_attribute(); attr; attr = attr.next_attribute())
        {
            if(attr.get_userdata()) continue;   //�����Ѿ���Ԥ���������
            SetAttribute(attr.name(), attr.value(), TRUE);
        }
        if(attrClass)
        {
            attrClass.set_userdata(0);
        }
        //���ó�ʼ����ɽӿ�
        OnInitFinished(xmlNode);
        return TRUE;
    }

    SStringW SObject::tr( const SStringW &strSrc )
    {
        return TR(strSrc,L"");
    }

}//end of namespace