/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       DuiCmnCtrl.h
 * @brief      ͨ�ÿؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-06-26
 * 
 * Describe    ComboBox�ؼ�
 */
#pragma once
#include "duiwnd.h"
#include "DuiRichEdit.h"
#include "DuiDropDown.h"
#include "duilistbox.h"
#include "duilistboxex.h"
#include "DuiCmnCtrl.h"

namespace SOUI
{

#define IDC_CB_EDIT          -100
#define IDC_DROPDOWN_LIST    -200

class CDuiComboBoxBase;


/**
 * @class      CComboEdit
 * @brief      ������CommboBox
 * 
 * Describe    �����������б�
 */
class CComboEdit:public SEdit
{
public:
    /**
     * CComboEdit::CComboEdit
     * @param    CDuiComboBoxBase *pOwner  -- ����       
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CComboEdit(CDuiComboBoxBase *pOwner);
    
    /**
     * CComboEdit::~CComboEdit
     * @brief    ��������
     *
     * Describe  ��������
     */
    virtual ~CComboEdit(){}
protected:
    /**
     * CComboEdit::OnMouseHover
     * @brief    ���������ͣ�¼�
     * @param    WPARAM wParam 
     * @param    CPoint ptPos -- �������λ��
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnMouseHover(WPARAM wParam, CPoint ptPos);
    /**
     * CComboEdit::OnMouseLeave
     * @brief    ��������뿪�¼�
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */    
    void OnMouseLeave();
    /**
     * CComboEdit::OnKeyDown
     * @brief    ���̰����¼�
     * @param    UINT nChar -- ������Ӧ����ֵ 
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */   
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    /**
     * CComboEdit::DuiNotify
     * @brief    ֪ͨ��Ϣ
     * @param    LPSNMHDR pnms -- ���� 
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */   
    virtual LRESULT DuiNotify(LPSNMHDR pnms);

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_MOUSEHOVER(OnMouseHover)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_KEYDOWN(OnKeyDown)
    SOUI_MSG_MAP_END()
};

/**
 * @class      CComboEdit
 * @brief      ������CommboBox
 * 
 * Describe    �����������б�
 */
class SOUI_EXP CDuiComboBoxBase 
    : public SWindow
    , public ISDropDownOwner
{
    friend class CComboListBox;
public:
    
    /**
     * CDuiComboBoxBase::CDuiComboBoxBase
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiComboBoxBase(void);
    
    /**
     * CDuiComboBoxBase::~CDuiComboBoxBase
     * @brief    ��������
     *
     * Describe  ��������
     */
    virtual ~CDuiComboBoxBase(void);
    /**
     * CDuiComboBoxBase::GetCurSel
     * @brief    ��ȡѡ��ֵ����
     * @return   ����int  
     *
     * Describe  ��ȡ��ǰѡ������
     */
    virtual int GetCurSel() const =0;

    /**
     * CDuiComboBoxBase::GetWindowText
     * @brief    ��ȡ���ڱ���
     * @return   ����CDuiStringT
     *
     * Describe  ��ȡ��ǰѡ������
     */
    virtual SStringT GetWindowText() =0;

    /**
     * CDuiComboBoxBase::DropDown
     * @brief    �����¼�
     *
     * Describe  �����¼�
     */
    void DropDown();
    
    /**
     * CDuiComboBoxBase::CloseUp
     * @brief    �����ر�
     *
     * Describe  �����ر�
     */
    void CloseUp();
protected:
    /**
     * CDuiComboBoxBase::GetDropDownOwner
     * @brief    ��ȡowner
     * @return   SWindow
     *
     * Describe  ��ȡowner
     */
    virtual SWindow* GetDropDownOwner();

    /**
     * CDuiComboBoxBase::OnDropDown
     * @brief    �����¼�
     * @param     SDropDownWnd *pDropDown -- ��������ָ��
     *
     * Describe  �����¼�
     */
    virtual void OnDropDown(SDropDownWnd *pDropDown);

    /**
     * CDuiComboBoxBase::OnCloseUp
     * @brief    �����¼�
     * @param     SDropDownWnd *pDropDown -- ��������ָ��
     * @param     UINT uCode -- ��Ϣ��
     *
     * Describe  �����ر�
     */
    virtual void OnCloseUp(SDropDownWnd *pDropDown,UINT uCode);
protected:
    /**
     * CDuiComboBoxBase::OnSelChanged
     * @brief    �������ڸı��¼�
     *
     * Describe  �����ر�
     */
    virtual void OnSelChanged();

    /**
     * CDuiComboBoxBase::DuiNotify
     * @brief    ֪ͨ��Ϣ
     * @param    LPSNMHDR pnms -- ���� 
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */ 
    virtual LRESULT DuiNotify(LPSNMHDR pnms);
    
protected:

    /**
     * CDuiComboBoxBase::CalcPopupRect
     * @brief    ���㵯������λ��
     * @param    int nHeight -- �������ڸ߶�
     * @param    CRect & rcPopup -- ���浯������Rect
     * @return   BOOL  TRUE -- �ɹ�  FALSE -- ʧ��
     *
     * Describe  ���㵯������λ��,������rcPopup��
     */    
    BOOL CalcPopupRect(int nHeight,CRect & rcPopup);
    
    /**
     * CDuiComboBoxBase::CreateListBox
     * @brief    ���������б�
     * @param    pugi::xml_node xmlNode  -- xml����
     * @return   BOOL  TRUE -- �ɹ�  FALSE -- ʧ��
     *
     * Describe  ���������б�
     */    
    virtual BOOL CreateListBox(pugi::xml_node xmlNode)=0;
    
    /**
     * CDuiComboBoxBase::GetListBoxHeight
     * @brief    ��ȡ�����б�߶�
     * @return   ����int �߶�
     *
     * Describe  ��ȡ�����б�߶�
     */        
    virtual int  GetListBoxHeight()=0;

    /**
     * CDuiComboBoxBase::GetDropBtnRect
     * @brief    ��ȡ�����б�ťλ��
     * @param    LPRECT prc -- ��ťRect
     *
     * Describe  ��ȡ�����б��Ҳఴťλ��
     */        
    void GetDropBtnRect(LPRECT prc);
    /**
     * CDuiComboBoxBase::LoadChildren
     * @brief    ��������
     * @param    pugi::xml_node xmlNode  -- xml�ļ�
     * @return   ����BOOL  TRUE -- �ɹ� FALSE -- ʧ��
     *
     * Describe  ��������
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);    
    /**
     * CDuiComboBoxBase::GetTextRect
     * @brief    ��ȡ�ı�λ��
     * @param    LPRECT pRect -- �ı�λ��
     *
     * Describe  ��ȡ�ı�λ��
     */
    virtual void GetTextRect(LPRECT pRect);
    /**
     * CDuiComboBoxBase::OnPaint
     * @brief    ������Ϣ
     * @param    IRenderTarget * pRT -- ����
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnPaint(IRenderTarget * pRT);
    
    /**
     * CDuiComboBoxBase::OnLButtonDown
     * @brief    ��������¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnLButtonDown(UINT nFlags,CPoint pt);

    /**
     * CDuiComboBoxBase::OnMouseMove
     * @brief    ��������ƶ��¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnMouseMove(UINT nFlags,CPoint pt);

    /**
     * CDuiComboBoxBase::OnMouseLeave
     * @brief    ��������ƶ��¼�
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnMouseLeave();

    /**
     * CDuiComboBoxBase::OnKeyDown
     * @brief    ���̰����¼�
     * @param    UINT nChar -- ������Ӧ����ֵ 
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    /**
     * CDuiComboBoxBase::OnChar
     * @brief    �ַ���Ϣ
     * @param    UINT nChar -- ������Ӧ����ֵ 
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */ 
    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    /**
     * CDuiComboBoxBase::OnDestroy
     * @brief    ������������
     * 
     * Describe  �˺���������������������
     */  
    void OnDestroy();
    /**
     * CDuiComboBoxBase::OnGetDuiCode
     * @brief    ��ȡ��Ϣ��
     * 
     * Describe  ��ȡ��Ϣ��
     */  
    UINT OnGetDlgCode();
    
    /**
     * CDuiComboBoxBase::IsTabStop
     * @brief    �Ƿ��ֹTAB��
     * 
     * Describe  �Ƿ��ֹTAB��
     */  
    BOOL IsTabStop();

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"dropdown", m_bDropdown, FALSE)
        ATTR_INT(L"dropheight", m_nDropHeight, FALSE)
         ATTR_INT(L"cursel", m_iInitSel, FALSE)
        ATTR_SKIN(L"btnskin", m_pSkinBtn, FALSE)
        ATTR_INT(L"animtime", m_iAnimTime, FALSE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)        
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_KEYDOWN(OnKeyDown) 
        MSG_WM_CHAR(OnChar)
        MSG_WM_DESTROY(OnDestroy)
    SOUI_MSG_MAP_END()

protected:
    /**
     * CDuiComboBoxBase::GetEditText
     * @brief    ��ȡ�༭������
     * 
     * Describe  ��ȡ�༭������
     */  
    SStringT GetEditText()
    {
        if(!m_bDropdown)
        {
            int nLen=m_pEdit->GetWindowTextLength();
            wchar_t *pszBuf=new wchar_t[nLen+1];
            m_pEdit->GetWindowText(pszBuf,nLen);
            pszBuf[nLen]=0;
            SStringT str=DUI_CW2T(pszBuf);
            delete pszBuf;
            return str;
        }
        else
        {
            return SStringT();
        }
    }

    SRichEdit *m_pEdit;      /**< SRichEditָ�� */
    DWORD     m_dwBtnState;  /**< ��ť״̬      */
    ISkinObj *m_pSkinBtn;    /**< ��ť��Դ      */
    
    BOOL m_bDropdown;        /**< �Ƿ���   */
    int  m_nDropHeight;      /**< ������߶� */
    int  m_iAnimTime;        /**< ����ʱ��   */
    int  m_iInitSel;         /**< Ĭ��ѡ������ */
    SDropDownWnd *m_pDropDownWnd;  /**< DropDownָ�� */
};

/**
 * @class      SComboBox
 * @brief      ������CommboBox
 * 
 * Describe    �����������б�
 */
class SOUI_EXP SComboBox : public CDuiComboBoxBase
{
    SOUI_CLASS_NAME(SComboBox, L"combobox")
public:
    /**
     * SComboBox::SComboBox
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    SComboBox();
      
    /**
     * SComboBox::~SComboBox
     * @brief    ��������
     *
     * Describe  ��������
     */
    virtual ~SComboBox();

    /**
     * SComboBox::SetCurSel
     * @brief    ���õ�ǰѡ��
     * @param    int iSel -- ѡ������
     * 
     * Describe  ���õ�ǰѡ��
     */ 
    BOOL SetCurSel(int iSel)
    {
        if(m_pListBox->SetCurSel(iSel))
        {
            OnSelChanged();
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    /**
     * SComboBox::GetCurSel
     * @brief    ��ȡѡ������
     * @return   ����int -- ѡ������
     * 
     * Describe  ��ȡѡ������
     */ 
    int GetCurSel() const
    {
        return m_pListBox->GetCurSel();
    }

    /**
     * SComboBox::GetCount
     * @brief    ��ȡ���������
     * @return   ����int
     * 
     * Describe  ��ȡ���������
     */ 
    int  GetCount()
    {
        return m_pListBox->GetCount();
    }
    /**
     * SComboBox::GetTextRect
     * @brief    ��ȡ�ı�λ��
     * @param    LPRECT pRect -- �ı�λ��
     *
     * Describe  ��ȡ�ı�λ��
     */
    SStringT GetWindowText()
    {
        if(!m_bDropdown)
        {
            return GetEditText();
        }
        if(m_pListBox->GetCurSel()==-1) return _T("");
        return GetLBText(m_pListBox->GetCurSel());
    }

    /**
     * SComboBox::GetItemData
     * @brief    ��ȡ��������
     * @param    UINT iItem -- ѡ��ֵ
     *
     * Describe  ��ȡ��������
     */
    LPARAM GetItemData(UINT iItem) const
    {
        return m_pListBox->GetItemData(iItem);
    }

    /**
     * SComboBox::SetItemData
     * @brief    ���ø�������
     * @param    UINT iItem -- ����ֵ
     * @param    LPARAM lParam -- ����ֵ
     *
     * Describe  ���ø�������
     */
    int SetItemData(UINT iItem, LPARAM lParam)
    {
        return m_pListBox->SetItemData(iItem,lParam);
    }

    /**
     * SComboBox::InsertItem
     * @brief    ��������
     * @param    UINT iPos -- λ��
     * @param    LPCTSTR pszText -- �ı�ֵ
     * @param    int iIcon -- ͼ��
     * @param    LPARAM lParam -- ����ֵ
     *
     * Describe  ��������
     */
    int InsertItem(UINT iPos,LPCTSTR pszText,int iIcon,LPARAM lParam)
    {
        return m_pListBox->InsertString(iPos,pszText,iIcon,lParam);
    }

    /**
     * SComboBox::DeleteString
     * @brief    ɾ��ĳһ��
     * @param    UINT iItem -- ����ֵ
     *
     * Describe  ɾ��ĳһ��
     */
    BOOL DeleteString(UINT iItem)
    {
        return m_pListBox->DeleteString(iItem);
    }

    /**
     * SComboBox::ResetContent
     * @brief    ɾ��������
     *
     * Describe  ���ø�������
     */
    void ResetContent()
    {
        return m_pListBox->DeleteAll();
    }

    /**
     * SComboBox::GetLBText
     * @brief    ��ȡ�ı�
     * @param    int iItem -- ����ֵ
     *
     * Describe  ��ȡ�ı�
     */
    SStringT GetLBText(int iItem)
    {
        SStringT strText;
        m_pListBox->GetText(iItem,strText);
        return strText;
    }
    /**
     * SComboBox::GetListBox
     * @brief    ��ȡ�����б�ָ��
     * @param    ����SListBox * 
     *
     * Describe  ��ȡ�����б�ָ��
     */
    SListBox * GetListBox(){return m_pListBox;}
    
protected:
    /**
     * SComboBox::CreateListBox
     * @brief    ���������б�
     * @param    ����BOOL TRUE -- �ɹ� FALSE -- ʧ��
     *
     * Describe  ���������б�
     */
    virtual BOOL CreateListBox(pugi::xml_node xmlNode);
    
    /**
     * SComboBox::GetListBoxHeight
     * @brief    ��ȡ�����б�߶�
     * @param    ����int
     *
     * Describe  ��ȡ�����б�߶�
     */
    virtual int  GetListBoxHeight();

    /**
     * SComboBox::OnDropDown
     * @brief    �����б��¼�
     * @param    SDropDownWnd *pDropDown -- �����б�ָ��
     *
     * Describe  �����б��¼�
     */
    virtual void OnDropDown(SDropDownWnd *pDropDown);

    /**
     * SComboBox::OnCloseUp
     * @brief    �����б�ر��¼�
     * @param    SDropDownWnd *pDropDown -- �����б�ָ��
     * @param    UINT uCode -- ��Ϣ��
     *
     * Describe  ��ȡ�����б�ָ��
     */
    virtual void OnCloseUp(SDropDownWnd *pDropDown,UINT uCode);
    
    /**
     * SComboBox::OnSelChanged
     * @brief    �����б�selected�¼�
     *
     * Describe  �����б�selected�¼�
     */
    virtual void OnSelChanged();

protected:

    SListBox *m_pListBox;  /**< SListBoxָ�� */
};

class SOUI_EXP SComboBoxEx : public CDuiComboBoxBase
{
    SOUI_CLASS_NAME(SComboBoxEx, L"comboboxex")
public:
    /**
     * SComboBoxEx::SComboBoxEx
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    SComboBoxEx();
    /**
     * SComboBoxEx::~SComboBoxEx
     * @brief    ��������
     *
     * Describe  ��������
     */    
    virtual ~SComboBoxEx();

    /**
     * SComboBoxEx::SetCurSel
     * @brief    ���õ�ǰѡ��
     * @param    int iSel -- ѡ������
     * 
     * Describe  ���õ�ǰѡ��
     */
    BOOL SetCurSel(int iSel)
    {
        if(m_pListBox->SetCurSel(iSel))
        {
            OnSelChanged();
            return TRUE;
        }else
        {
            return FALSE;
        }
    }

    /**
     * SComboBoxEx::GetCurSel
     * @brief    ��ȡѡ������
     * @return   ����int -- ѡ������
     * 
     * Describe  ��ȡѡ������
     */ 
    int GetCurSel() const
    {
        return m_pListBox->GetCurSel();
    }

    /**
     * SComboBox::GetCount
     * @brief    ��ȡ���������
     * @return   ����int
     * 
     * Describe  ��ȡ���������
     */ 
    int  GetCount()
    {
        return m_pListBox->GetItemCount();
    }
    
    /**
     * SComboBoxEx::GetTextRect
     * @brief    ��ȡ�ı�λ��
     * @param    LPRECT pRect -- �ı�λ��
     *
     * Describe  ��ȡ�ı�λ��
     */
    SStringT GetWindowText()
    {
        if(!m_bDropdown) return GetEditText();
        return GetLBText(m_pListBox->GetCurSel());
    }

    /**
     * SComboBoxEx::GetItemData
     * @brief    ��ȡ��������
     * @param    UINT iItem -- ѡ��ֵ
     *
     * Describe  ��ȡ��������
     */
    LPARAM GetItemData(UINT iItem) const
    {
        return m_pListBox->GetItemData(iItem);
    }

    /**
     * SComboBoxEx::SetItemData
     * @brief    ���ø�������
     * @param    UINT iItem -- ����ֵ
     * @param    LPARAM lParam -- ����ֵ
     *
     * Describe  ���ø�������
     */
    void SetItemData(UINT iItem, LPARAM lParam)
    {
        m_pListBox->SetItemData(iItem,lParam);
    }
    
    /**
     * SComboBoxEx::InsertItem
     * @brief    ��������
     * @param    UINT iPos -- λ��
     * @param    LPCTSTR pszText -- �ı�ֵ
     * @param    int iIcon -- ͼ��
     * @param    LPARAM lParam -- ����ֵ
     *
     * Describe  ��������
     */

    int InsertItem(UINT iPos,LPCTSTR pszText,int iIcon,LPARAM lParam)
    {
        int iInserted= m_pListBox->InsertItem(iPos,NULL,lParam);
        if(iInserted!=-1)
        {
            SWindow *pWnd=m_pListBox->GetItemPanel(iInserted);
            if(m_uTxtID!=0)
            {
                SWindow *pText=pWnd->FindChildByID(m_uTxtID);
                if(pText) pText->SetInnerText(pszText);
            }
            if(m_uIconID!=0)
            {
                SImageWnd *pIcon=pWnd->FindChildByID2<SImageWnd>(m_uIconID);
                if(pIcon) pIcon->SetIcon(iIcon);
            }
        }
        return iInserted;
    }
    /**
     * SComboBoxEx::DeleteString
     * @brief    ɾ��ĳһ��
     * @param    UINT iItem -- ����ֵ
     *
     * Describe  ɾ��ĳһ��
     */
    void DeleteString(UINT iItem)
    {
        m_pListBox->DeleteItem(iItem);
    }

    /**
     * SComboBoxEx::ResetContent
     * @brief    ɾ��������
     *
     * Describe  ���ø�������
     */
    void ResetContent()
    {
        return m_pListBox->DeleteAllItems();
    }
    
    /**
     * SComboBoxEx::GetLBText
     * @brief    ��ȡ�ı�
     * @param    int iItem -- ����ֵ
     *
     * Describe  ��ȡ�ı�
     */
    SStringT GetLBText(int iItem)
    {
        if(m_uTxtID == 0 || iItem<0 || iItem>= GetCount()) return _T("");
        SWindow *pItem=m_pListBox->GetItemPanel(iItem);
        SWindow *pText=pItem->FindChildByID(m_uTxtID);
        if(!pText) return _T("");
        return pText->GetInnerText();
    }

    SListBoxEx * GetListBox(){return m_pListBox;}

protected:
    
    /**
     * SComboBox::OnSelChanged
     * @brief    �����б�selected�¼�
     *
     * Describe  �����б�selected�¼�
     */
    virtual void OnSelChanged();
protected:
    /**
     * SComboBoxEx::CreateListBox
     * @brief    ���������б�
     * @param    ����BOOL TRUE -- �ɹ� FALSE -- ʧ��
     *
     * Describe  ���������б�
     */
    virtual BOOL CreateListBox(pugi::xml_node xmlNode);

    /**
     * SComboBoxEx::GetListBoxHeight
     * @brief    ��ȡ�����б�߶�
     * @param    ����int
     *
     * Describe  ��ȡ�����б�߶�
     */    
    virtual int  GetListBoxHeight();

    /**
     * SComboBoxEx::OnDropDown
     * @brief    �����б��¼�
     * @param    SDropDownWnd *pDropDown -- �����б�ָ��
     *
     * Describe  �����б��¼�
     */
    virtual void OnDropDown(SDropDownWnd *pDropDown);

    /**
     * SComboBox::OnCloseUp
     * @brief    �����б�ر��¼�
     * @param    SDropDownWnd *pDropDown -- �����б�ָ��
     * @param    UINT uCode -- ��Ϣ��
     *
     * Describe  ��ȡ�����б�ָ��
     */
    virtual void OnCloseUp(SDropDownWnd *pDropDown,UINT uCode);

protected:

    SOUI_ATTRS_BEGIN()
        ATTR_UINT(L"id_text", m_uTxtID, FALSE)
        ATTR_UINT(L"id_icon", m_uIconID, FALSE)
    SOUI_ATTRS_END()

    SListBoxEx *m_pListBox;  /**< SListBoxָ�� */
    UINT   m_uTxtID;  /**< �ı�ID */
    UINT   m_uIconID; /**< ͼ��ID */
};

}//namespace
