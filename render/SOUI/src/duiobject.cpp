#include "duistd.h"
#include "duiobject.h"

namespace SOUI
{


    BOOL SObject::Load( pugi::xml_node xmlNode )
    {
        if(!xmlNode) return FALSE;
#ifdef _DEBUG
        {
            pugi::xml_writer_buff writer;
            xmlNode.print(writer);
            m_strXml=DUI_CA2A(CDuiStringA(writer.buffer(),writer.size()),CP_UTF8);
        }
#endif

        //�������������Ĭ������
        pugi::xml_node defAttr = GETCSS(GetObjectClass());
        if(defAttr)
        {
            //���ȴ���"class"����
            pugi::xml_attribute attrClass=defAttr.attribute("class");
            if(attrClass) SetAttribute(attrClass.name(), attrClass.value(), TRUE);
            for (pugi::xml_attribute attr = defAttr.first_attribute(); attr; attr = attr.next_attribute())
            {
                if(strcmp(attr.name(),"class")==0) continue;
                SetAttribute(attr.name(), attr.value(), TRUE);
            }
        }

        //���õ�ǰ���������

        //���ȴ���"class"����
        pugi::xml_attribute attrClass=xmlNode.attribute("class");
        if(attrClass) SetAttribute(attrClass.name(), attrClass.value(), TRUE);
        for (pugi::xml_attribute attr = xmlNode.first_attribute(); attr; attr = attr.next_attribute())
        {
            if(strcmp(attr.name(),"class")==0) continue;
            SetAttribute(attr.name(), attr.value(), TRUE);
        }
        OnAttributeFinish(xmlNode);
        return TRUE;
    }
}//end of namespace