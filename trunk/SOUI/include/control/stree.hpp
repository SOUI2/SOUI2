/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       stree.hpp
 * @brief      ��ģ��--�ṩ��һ�����������ʵ�����ṹ
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-13
 * 
 * Describe    �������������ڵĸ��� ֻ��Ҫ�������༴��
 *
 *              version: 1.0��2003-10-24 ʵ�ֻ�������
 *                       2.0  2004-12-29 �������������ӿڣ��޸��ڴ��ͷŲ��ֿ��ܴ��ڵ�bug
 *                       2.1  2006-10-17 Ϊ�ڵ�����һ��hChildLast����,�Լӿ������ݲ���ʱ���ٶ�
 *                       2.2  2008-10-16 �޸�һ�������ӿڵ�����
 *                       2.3  2011-10-17 �������ͷŵĽӿڴӻص������ĳ��麯��
 */
#if !defined(AFX_STREE_H__D2332B4E_2C7E_4357_BE22_EC55BF496C1C__INCLUDED_)
#define AFX_STREE_H__D2332B4E_2C7E_4357_BE22_EC55BF496C1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef SASSERT
#define SASSERT(x)
#endif

//typedef ULONG_PTR HSTREEITEM;

#define STVI_ROOT    ((HSTREEITEM)0xFFFF0000)//=TVI_ROOT
#define STVI_FIRST    ((HSTREEITEM)0xFFFF0001)//=TVI_FIRST
#define STVI_LAST    ((HSTREEITEM)0xFFFF0002)//=TVI_LAST
#define STVN_ROOT    ((HSTREENODE)(ULONG_PTR)0xFFFF0000)//=STVN_ROOT
#define STVN_FIRST    ((HSTREENODE)(ULONG_PTR)0xFFFF0001)//=STVN_FIRST
#define STVN_LAST    ((HSTREENODE)(ULONG_PTR)0xFFFF0002)//=STVN_LAST
#define STVL_ROOT    ((PSTREELINK)0xFFFF0000)

/**
 * @class      CSTree ģ����
 * @brief      CSTree ģ����
 * 
 * Describe    CSTree ģ����
 */
template<class T>
class SOUI_EXP CSTree  
{
    /**
     * @class      _STREENODE
     * @brief      �ڵ�ṹ��
     * 
     * Describe    �ڵ�ṹ��
     */
    typedef struct _STREENODE{
        struct _STREENODE *hParent;      /**< ���ڵ� */
        struct _STREENODE *hChildFirst;  /**< ��һ���ӽڵ� */
        struct _STREENODE *hChildLast;   /**< ���һ���ӽڵ� */
        struct _STREENODE *hPrevSibling; /**< �ֽڵ� */
        struct _STREENODE *hNextSibling; /**< �ܽڵ� */
        T data;                          /**< ���� */
    }STREENODE,*HSTREENODE;

    /**
     * @class      _STREELINK
     * @brief      ����������
     * 
     * Describe    �˽ṹ�������������ڵ�
     */
    typedef struct _STREELINK{
        HSTREENODE  hParent;       /**< ���ڵ� */
        HSTREENODE  hChildFirst;   /**< ��һ���ӽڵ� */
        HSTREENODE  hChildLast;    /**< ���һ���ӽڵ� */
        HSTREENODE  hPrevSibling;  /**< �ֽڵ� */
        HSTREENODE  hNextSibling;  /**< �ܽڵ� */
    }STREELINK,*PSTREELINK;
    
    /**
     * �ص�����
     * @brief    �������������������¼�
     * @param    T *:��ǰ�������Ľ�������
     * @param    LPARAM:�ص�ʱʹ�õĲ���
     * @return   FALSE��������TRUE���жϱ���
     *
     * Describe  ����һ�������Ļص�����ԭ�ͣ�
     */
    typedef BOOL (*CBTRAVERSING)(T*,LPARAM);

public:
    /**
     * CSTree::CSTree
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */  
    CSTree()
    {
        m_hRootFirst=NULL;
        m_hRootLast=NULL;
    }

    /**
     * CSTree::~CSTree
     * @brief    ��������
     *
     * Describe  ��������
     */ 
    virtual ~CSTree(){DeleteAllItems();}

    /**
     * CSTree::DeleteAllItems
     * @brief    ɾ�����нڵ�
     *
     * Describe  ɾ�����нڵ�
     */
    void DeleteAllItems(){
        if(m_hRootFirst)
        {
            FreeNode(STVN_ROOT);
            m_hRootFirst=NULL;
            m_hRootLast=NULL;
        }
    }
    
    /**
     * CSTree::GetNextSiblingItem
     * @brief    ��ȡ��һ���ֵ�
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����HSTREEITEM
     *
     * Describe  ��ȡ��һ���ֵ�
     */
    static HSTREEITEM GetNextSiblingItem(HSTREEITEM hItem){
        PSTREELINK pLink= (PSTREELINK)hItem;
        SASSERT(pLink&&pLink!=STVL_ROOT);
        return (HSTREEITEM)pLink->hNextSibling;
    }

    /**
     * CSTree::GetPrevSiblingItem
     * @brief    ��ȡ��һ���ֵ�
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����HSTREEITEM
     *
     * Describe  ��ȡ��һ���ֵ�
     */
    static HSTREEITEM GetPrevSiblingItem(HSTREEITEM hItem)
    {
        PSTREELINK pLink= (PSTREELINK)hItem;
        SASSERT(pLink&&pLink!=STVL_ROOT);
        return (HSTREEITEM)pLink->hPrevSibling;
    }
    
    /**
     * CSTree::GetParentItem
     * @brief    ��ȡ�����
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����HSTREEITEM
     *
     * Describe  ��ȡ�����
     */
    static HSTREEITEM GetParentItem(HSTREEITEM hItem)
    {
        PSTREELINK pLink= (PSTREELINK)hItem;
        SASSERT(pLink&&pLink!=STVL_ROOT);
        return (HSTREEITEM)pLink->hParent;
    }
    
    /**
     * CSTree::GetItemLevel
     * @brief    ��ȡ������
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����int
     *
     * Describe  ��ȡ������
     */
    static int GetItemLevel(HSTREEITEM hItem)
    {
        int nRet=-1;
        if(hItem==STVI_ROOT) hItem=NULL;
        while(hItem)
        {
            nRet++;
            hItem=GetParentItem(hItem);
        }
        return nRet;
    }

    /**
     * CSTree::GetChildItem
     * @brief    ��ȡ��һ���ӽ��
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @param    BOOL bFirst       -- �Ƿ��һ���ڵ�
     * @return   ����HSTREEITEM
     *
     * Describe  ��ȡ��һ���ӽ��
     */
    HSTREEITEM GetChildItem(HSTREEITEM hItem,BOOL bFirst=TRUE)
    {
        HSTREENODE hsNode= (HSTREENODE)hItem;
        SASSERT(hsNode);
        if(hsNode==STVN_ROOT)
        {
            if(bFirst)
                return (HSTREEITEM)m_hRootFirst;
            else
                return (HSTREEITEM)m_hRootLast;
        }
        else
        {
            if(bFirst)
                return (HSTREEITEM)hsNode->hChildFirst;
            else
                return (HSTREEITEM)hsNode->hChildLast;
        }
    }
    
    /**
     * CSTree::GetChildrenCount
     * @brief    ��ȡ�ӽ������
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����int
     *
     * Describe  ��ȡ�ӽ������
     */
    int GetChildrenCount(HSTREEITEM hItem)
    {
        int nRet=0;
        HSTREEITEM hChild=GetChildItem(hItem);
        while(hChild)
        {
            nRet++;
            hChild=GetNextSiblingItem(hChild);
        }
        return nRet;
    }

    /**
     * CSTree::DeleteItem
     * @brief    ɾ��һ���ڵ㣬���Ա�����������
     * @param    HSTREEITEM hItem  -- �ڵ�
     *
     * Describe  ɾ��һ���ڵ㣬���Ա�����������
     */
    virtual void DeleteItem(HSTREEITEM hItem)
    {
        HSTREENODE hsNode= (HSTREENODE)hItem;
        SASSERT(hsNode);
        if(hsNode==STVN_ROOT)
        {
            FreeNode(STVN_ROOT);
            m_hRootFirst=NULL;
            m_hRootLast=NULL;
            return;
        }
        STREENODE nodeCopy=*hsNode;
        BOOL bRootFirst=hsNode==m_hRootFirst;
        BOOL bRootLast=hsNode==m_hRootLast;
        FreeNode(hsNode);

        if(nodeCopy.hPrevSibling)//has prevsibling
            nodeCopy.hPrevSibling->hNextSibling=nodeCopy.hNextSibling;
        else if(nodeCopy.hParent)//parent's first child
            nodeCopy.hParent->hChildFirst=nodeCopy.hNextSibling;
        if(nodeCopy.hNextSibling)// update next sibling's previous sibling
            nodeCopy.hNextSibling->hPrevSibling=nodeCopy.hPrevSibling;
        else if(nodeCopy.hParent)//parent's last child
            nodeCopy.hParent->hChildLast=nodeCopy.hPrevSibling;
        //update root item
        if(bRootFirst)    m_hRootFirst=nodeCopy.hNextSibling;
        if(bRootLast)   m_hRootLast=nodeCopy.hPrevSibling;
    }

    /**
     * CSTree::DeleteItemEx
     * @brief    ɾ��һ������֦������ý��ĸ����û�������ӽڵ���һ��ɾ��
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����BOOL
     *
     * Describe  ɾ��һ������֦������ý��ĸ����û�������ӽڵ���һ��ɾ��
     */
    BOOL DeleteItemEx(HSTREEITEM hItem)
    {
        if(GetChildItem(hItem)) return FALSE;
        while(hItem && !GetChildItem(hItem))
        {
            HSTREEITEM hParent=GetParentItem(hItem);
            DeleteItem(hItem);
            hItem=hParent;
        }
        return TRUE;
    }

    /**
     * CSTree::GetItem
     * @brief    ��ȡ����б��������
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����T
     *
     * Describe  ��ȡ����б��������
     */
    static T GetItem(HSTREEITEM hItem){
        SASSERT(hItem!=STVI_ROOT);
        HSTREENODE hsNode= (HSTREENODE)hItem;
        SASSERT(hsNode);
        return hsNode->data;
    }
    
    /**
     * CSTree::GetItemPt
     * @brief    ��ȡ����б��������
     * @param    HSTREEITEM hItem  -- �ڵ�
     * @return   ����T*
     *
     * Describe  ��ȡ����б��������
     */
    static T *GetItemPt(HSTREEITEM hItem){
        SASSERT(hItem!=STVI_ROOT);
        HSTREENODE hsNode= (HSTREENODE)hItem;
        SASSERT(hsNode);
        return &hsNode->data;
    }

    /**
     * CSTree::InsertItem
     * @brief    ����һ���½��
     * @param    const T &data -- �������
     * @param    HSTREEITEM hParent -- �½��ĸ����
     * @param    HSTREEITEM hInsertAfter -- �½���ǰһ���ֵܽ��
     * @return   ����HSTREEITEM �½���ָ��
     *
     * Describe  ��ȡ����б��������
     */
    HSTREEITEM InsertItem(const T &data,HSTREEITEM hParent=STVI_ROOT,HSTREEITEM hInsertAfter=STVI_LAST){
        HSTREENODE hParentNode=(HSTREENODE) hParent;
        HSTREENODE hInsertAfterNode=(HSTREENODE) hInsertAfter;
        if(hParentNode==STVN_ROOT)
            hParentNode=NULL;
        SASSERT(hInsertAfter);
        if(hInsertAfterNode!=STVN_FIRST && hInsertAfterNode!=STVN_LAST)
        {
            if(hInsertAfterNode->hParent!=hParentNode) return NULL;
            if(hInsertAfterNode->hNextSibling==NULL) hInsertAfterNode=STVN_LAST;
        }

        HSTREENODE hInserted=new STREENODE;
        hInserted->data=data;
        hInserted->hParent=hParentNode;
        hInserted->hChildFirst=NULL;
        hInserted->hChildLast=NULL;

        if(hInsertAfterNode==STVN_FIRST)
        {
            hInserted->hPrevSibling=NULL;
            if(hParentNode==NULL)//root
            {
                hInserted->hNextSibling=m_hRootFirst;
                if(m_hRootFirst) m_hRootFirst->hPrevSibling=hInserted;
                m_hRootFirst=hInserted;
                if(m_hRootLast==NULL) m_hRootLast=hInserted;
            }else    //has parent
            {
                hInserted->hNextSibling=hParentNode->hChildFirst;
                if(hInserted->hNextSibling)
                {
                    hInserted->hNextSibling->hPrevSibling=hInserted;
                    hParentNode->hChildFirst=hInserted;
                }else
                {
                    hParentNode->hChildLast=hParentNode->hChildFirst=hInserted;
                }
            }
        }else if(hInsertAfterNode==STVN_LAST)
        {
            hInserted->hNextSibling=NULL;
            if(hParentNode==NULL)//root
            {
                hInserted->hPrevSibling=m_hRootLast;
                if(m_hRootLast) m_hRootLast->hNextSibling=hInserted;
                m_hRootLast=hInserted;
                if(!m_hRootFirst) m_hRootFirst=hInserted;
            }else
            {
                hInserted->hPrevSibling=hParentNode->hChildLast;
                if(hParentNode->hChildLast) 
                {
                    hInserted->hPrevSibling->hNextSibling=hInserted;
                    hParentNode->hChildLast=hInserted;
                }else
                {
                    hParentNode->hChildLast=hParentNode->hChildFirst=hInserted;
                }                
            }
        }else
        {
            HSTREENODE hNextSibling=hInsertAfterNode->hNextSibling;
            hInserted->hPrevSibling=hInsertAfterNode;
            hInserted->hNextSibling=hNextSibling;
            hNextSibling->hPrevSibling = hInsertAfterNode->hNextSibling = hInserted;
        }
        return (HSTREEITEM)hInserted;
    }

    /**
     * CSTree::TraversingRecursion
     * @brief    ���õݹ鷽ʽ����һ�������
     * @param    HSTREEITEM hItem -- ��ʼ���
     * @param    CBTRAVERSING funTraversing -- ִ��ʵ�ʲ����Ļص�����
     * @param    LPARAM lParam -- �ص�ʱʹ�õĲ���
     * @return   ����HSTREEITEM
     *
     * Describe  ���õݹ鷽ʽ����һ�������
     */
    HSTREEITEM TraversingRecursion(HSTREEITEM hItem,CBTRAVERSING funTraversing,LPARAM lParam)
    {
        SASSERT(hItem);
        if(hItem!=STVI_ROOT)
        {
            if(funTraversing(GetItemPt(hItem),lParam)) return hItem;
        }
        HSTREEITEM hChild=GetChildItem(hItem);
        while(hChild)
        {
            HSTREEITEM hTmp=GetChildItem(hChild);
            if(hTmp)
            {
                HSTREEITEM hRet=TraversingRecursion(hTmp,funTraversing,lParam);
                if(hRet) return hRet;
            }else
            {
                if(funTraversing(GetItemPt(hChild),lParam)) return hChild;
            }
            hChild=GetNextSiblingItem(hChild);
        }
        return NULL;
    }
   
    /**
     * CSTree::TraversingSequence
     * @brief    ��˳��ʽ��ָ����㿪ʼ���Һ���Ľ�㣬�����Լ����ӽڵ㼰�Լ����µ��ֵܽ��
     * @param    HSTREEITEM hItem -- ��ʼ���
     * @param    CBTRAVERSING funTraversing -- ִ��ʵ�ʲ����Ļص�����
     * @param    LPARAM lParam -- �ص�ʱʹ�õĲ���
     * @return   ����HSTREEITEM
     *
     * Describe  ��˳��ʽ��ָ����㿪ʼ���Һ���Ľ�㣬�����Լ����ӽڵ㼰�Լ����µ��ֵܽ��
     */
    HSTREEITEM TraversingSequence(HSTREEITEM hItem,CBTRAVERSING funTraversing,LPARAM lParam)
    {
        if(!m_hRootFirst) return NULL;
        if(hItem!=STVI_ROOT)
        {
            if(funTraversing(GetItemPt(hItem),lParam)) return hItem;
        }
        HSTREEITEM hNext=GetNextItem(hItem);
        while(hNext)
        {
            if(funTraversing(GetItemPt(hNext),lParam)) return hNext;
            hNext=GetNextItem(hNext);
        }
        return NULL;
    }

    /**
     * CSTree::GetRootItem
     * @brief    ��ȡ���ڵ�
     * @param    BOOL bFirst -- �Ƿ�Ӹ��ڵ�
     * @return   ����HSTREEITEM 
     *
     * Describe  ��ȡ���ڵ�
     */
    HSTREEITEM GetRootItem(BOOL bFirst=TRUE){
        return (HSTREEITEM)(bFirst?m_hRootFirst:m_hRootLast);
    }

    /**
     * CSTree::GetDesendants
     * @brief    ��ȡ������������
     * @param    HSTREEITEM hItem -- ��ʼ���
     * @return   ����int
     *
     * Describe  ��ȡ������������
     */
    int GetDesendants(HSTREEITEM hItem)
    {
        int nRet=0;
        HSTREEITEM hChild=GetChildItem(hItem);
        while(hChild)
        {
            nRet += 1+GetDesendants(hChild);
            hChild=GetNextSiblingItem(hChild);
        }
        return nRet;
    }

    /**
     * CSTree::GetNextItem
     * @brief    ��ȡ��ǰ������һ�����
     * @param    HSTREEITEM hItem -- ��ǰ���
     * @return   ����HSTREEITEM  ��ǰ������һ�����
     *
     * Describe  ��ȡ��ǰ������һ�����
     * �����ǰ������ӽ�㣬�򷵻��Լ��ĵ�һ���ӽ�㣬
     * ������������µ��ֵܽ�㣬�򷵻��Լ������ֵܽ�㡢
     * ���������Լ��ĸ����������ֵܽ��
     */
    HSTREEITEM GetNextItem(HSTREEITEM hItem)
    {
        if(hItem==STVI_ROOT) return (HSTREEITEM)m_hRootFirst;

        HSTREEITEM hRet=GetChildItem(hItem);
        if(hRet) return hRet;
        HSTREEITEM hParent=hItem;
        while(hParent)
        {
            hRet=GetNextSiblingItem(hParent);
            if(hRet) return hRet;
            hParent=GetParentItem(hParent);
        }
        return NULL;
    }

    /**
     * CSTree::GetNextItem
     * @brief    ��ȡ��ǰ������һ�����
     * @param    HSTREEITEM hItem -- ��ǰ���
     * @param    int &nLevel -- ��ǰ���(hItem)��Ŀ����(return)�Ĳ�ι�ϵ,
     *                          1-���ӹ�ϵ��0���ֵܹ�ϵ��-n����->�����ֵ�
     * @return   ����HSTREEITEM  ��ǰ������һ�����
     *
     * Describe  ��ȡ��ǰ������һ�����
     *           �����ǰ������ӽ�㣬�򷵻��Լ��ĵ�һ���ӽ�㣬
     *           ������������µ��ֵܽ�㣬�򷵻��Լ������ֵܽ�㡢
     *           ���������Լ��ĸ����������ֵܽ��
     */
    HSTREEITEM GetNextItem(HSTREEITEM hItem,int &nLevel)
    {
        if(hItem==STVI_ROOT)
        {
            nLevel=1;
            return (HSTREEITEM)m_hRootFirst;
        }

        HSTREEITEM hRet=GetChildItem(hItem);
        if(hRet)
        {
            nLevel=1;
            return hRet;
        }
        HSTREEITEM hParent=hItem;
        nLevel=0;
        while(hParent)
        {
            hRet=GetNextSiblingItem(hParent);
            if(hRet) return hRet;
            nLevel--;
            hParent=GetParentItem(hParent);
        }
        return NULL;
    }
private:
    /**
     * CSTree::FreeNode
     * @brief    ���ú�������ķ�ʽ�ͷŽ��ռ�õĿռ�
     * @param    HSTREENODE hsNode -- ��ǰ���
     *
     * Describe  ���ú�������ķ�ʽ�ͷŽ��ռ�õĿռ�
     */
    void FreeNode(HSTREENODE hsNode)
    {
        SASSERT(hsNode);
        HSTREENODE hSibling=(HSTREENODE)GetChildItem((HSTREEITEM)hsNode);
        while(hSibling)
        {
            HSTREENODE hNextSibling=hSibling->hNextSibling;
            FreeNode(hSibling);
            hSibling=hNextSibling;
        }
        if(hsNode!=STVN_ROOT)
        {
            OnNodeFree(hsNode->data);
            delete hsNode;
        }
    }

protected:
    /**
     * CSTree::OnNodeFree
     * @brief    ����������ʵ�����ݵ��ͷŲ���
     * @param    T & data -- ����
     *
     * Describe  ����������ʵ�����ݵ��ͷŲ���
     */
    virtual void OnNodeFree(T & data){}

    HSTREENODE  m_hRootFirst;  /**< ��һ�����ڵ� */
    HSTREENODE  m_hRootLast;   /**< ���һ�����ڵ� */
};

#endif // !defined(AFX_STREE_H__D2332B4E_2C7E_4357_BE22_EC55BF496C1C__INCLUDED_)
