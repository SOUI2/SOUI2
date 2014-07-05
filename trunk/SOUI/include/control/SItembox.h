/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       SItembox.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-03
 * 
 * Describe     
 */
#pragma once
#include "core/SPanel.h"

namespace SOUI
{

/**
 * @class      CDuiItemBox
 * @brief      ItemBox
 * 
 * Describe    ItemBox
 */
class SOUI_EXP CDuiItemBox
    : public SScrollView
{
    SOUI_CLASS_NAME(CDuiItemBox, L"itembox")
public:
    /**
     * CDuiItemBox::CDuiItemBox
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    CDuiItemBox();

    /**
     * CDuiItemBox::~CDuiItemBox
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~CDuiItemBox() {}
    
    /**
     * CDuiItemBox::InsertItem
     * @brief    ��������
     * @param    LPCWSTR pszXml -- xml�����ļ�
     * @param    int iItem -- ����
     * @param    BOOL bEnsureVisible -- �Ƿ���ʾ
     * @return   ����SWindow
     *
     * Describe  ��������  
     */
    SWindow* InsertItem(LPCWSTR pszXml,int iItem=-1,BOOL bEnsureVisible=FALSE);

    /**
     * CDuiItemBox::InsertItem
     * @brief    ��������
     * @param    LPCWSTR pszXml -- xml�����ļ�
     * @param    int iItem -- ����
     * @param    BOOL bEnsureVisible -- �Ƿ���ʾ
     * @return   ����SWindow
     *
     * Describe  ��������  
     */
    SWindow* InsertItem(pugi::xml_node xmlNode, int iItem=-1,BOOL bEnsureVisible=FALSE);

    /**
     * CDuiItemBox::RemoveItem
     * @brief    ɾ����
     * @param    UINT iItem -- ����
     * @return   ����BOOL
     *     
     * Describe  ɾ����  
     */
    BOOL RemoveItem(UINT iItem);

    /**
     * CDuiItemBox::RemoveItem
     * @brief    ɾ����
     * @param    SWindow * pChild -- ���ڽڵ�
     * @return   ����BOOL
     *
     * Describe  ɾ����  
     */
    BOOL RemoveItem(SWindow * pChild);

    /**
     * CDuiItemBox::SetNewPosition
     * @brief    ��������
     * @param    SWindow * pChild -- �ڵ�
     * @param    DWORD nPos -- λ��
     * @param    BOOL bEnsureVisible -- �Ƿ���ʾ
     * @return   ����BOOL
     *     
     * Describe  ��������  
     */
    BOOL SetNewPosition(SWindow * pChild, DWORD nPos, BOOL bEnsureVisible = TRUE);

    /**
     * CDuiItemBox::RemoveAllItems
     * @brief    ɾ������
     *
     * Describe  ɾ������  
     */
    void RemoveAllItems();

    /**
     * CDuiItemBox::GetItemCount
     * @brief    ��ȡ�����
     * @return   UINT
     *
     * Describe  ��ȡ�����  
     */
    UINT GetItemCount();

    /**
     * CDuiItemBox::PageUp
     * @brief    ��һҳ
     *
     * Describe  ��һҳ  
     */
    void PageUp();

    /**
     * CDuiItemBox::PageDown
     * @brief    ��һҳ
     *
     * Describe  ��һҳ  
     */
    void PageDown();

    /**
     * CDuiItemBox::EnsureVisible
     * @brief    ������ʾ
     * @param    SWindow *pItem  -- ĳ��ָ��
     *
     * Describe  ������ʾ  
     */
    void EnsureVisible(SWindow *pItem);

    /**
     * CDuiItemBox::GetItemPos
     * @brief    ��ȡĳ�������
     * @return   ����int
     *
     * Describe  ��ȡĳ�������  
     */
    int GetItemPos(SWindow * lpCurItem);

protected:
    int m_nItemWid; /**< Item��� */
    int m_nItemHei; /**< Item�߶�*/
    int m_nSepWid;  /**< */
    int m_nSepHei;  /**< */

    /**
     * CDuiItemBox::UpdateScroll
     * @brief    ���¹�����
     *
     * Describe  ���¹�����  
     */
    void UpdateScroll();

    /**
     * CDuiItemBox::GetItemRect
     * @brief    ��ȡĳ��λ��
     * @param    int iItem -- ĳ������
     * @return   ����int
     *
     * Describe  ��ȡĳ�������  
     */
    
    CRect GetItemRect(int iItem);

    /**
     * CDuiItemBox::BringWindowAfter
     * @brief    �����½ڵ�
     * @param    SWindow * pChild -- �½ڵ�
     * @param    SWindow * pInsertAfter -- λ�ýڵ�
     *
     * Describe  ��ĳ���ڵ������½ڵ�  
     */
    void BringWindowAfter(SWindow * pChild, SWindow * pInsertAfter);

    /**
     * CDuiItemBox::OnSize
     * @brief    ��Ϣ��Ӧ����
     * @param    UINT nType --
     * @param    CSize size -- 
     *
     * Describe  ��ȡĳ�������  
     */
    void OnSize(UINT nType, CSize size);

    /**
     * CDuiItemBox::UpdateChildrenPosition
     * @brief    �����ӽڵ�λ��
     *
     * Describe  �����ӽڵ�λ��  
     */
    virtual void UpdateChildrenPosition(){}//leave it empty

    /**
     * CDuiItemBox::ReLayout
     * @brief    ���²���
     *
     * Describe  ���²���  
     */
    void ReLayout();

    /**
     * CDuiItemBox::OnScroll
     * @brief    �����¼�
     * @param    BOOL bVertical -- �Ƿ�����ֱ
     * @param    UINT uCode -- ��Ϣ��
     * @param    int nPos -- λ��
     * @retur    ����int
     *
     * Describe  ��ȡĳ�������  
     */
    virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);

    /**
     * CDuiItemBox::GetScrollLineSize
     * @brief    ��ȡ��������С
     * @param    BOOL bVertical -- �Ƿ�����ֱ����
     * @retur    ����int
     *
     * Describe  ��ȡ��������С  
     */
    virtual int GetScrollLineSize(BOOL bVertical);

    /**
     * CDuiItemBox::CreateChildren
     * @brief    ��������
     * @param    pugi::xml_node xmlNode
     * @return   ����BOOL
     *
     * Describe  ��ȡĳ�������  
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);

    SOUI_ATTRS_BEGIN()
    ATTR_INT(L"itemwid", m_nItemWid, TRUE)
    ATTR_INT(L"itemhei", m_nItemHei, TRUE)
    ATTR_INT(L"sepwid", m_nSepWid, TRUE)
    ATTR_INT(L"sephei", m_nSepHei, TRUE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_SIZE(OnSize)
    SOUI_MSG_MAP_END()

};

}//namespace SOUI
