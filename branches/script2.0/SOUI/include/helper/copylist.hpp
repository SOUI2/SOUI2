#pragma  once

namespace SOUI
{
    /**
     * CopyList
     * @brief    �б�Copy
     * @param    SList<T> & sour --  ԴList
     * @param    SList<T> & dest --  Ŀ��List
     * @return   void
     * Describe  
     */    
    template<class T>
    void CopyList(SList<T> &sour,SList<T> &dest)
    {
        SASSERT(dest.IsEmpty());
        SPOSITION pos=sour.GetHeadPosition();
        while(pos)
        {
            T &t=sour.GetNext(pos);
            dest.AddTail(t);
        }
    }

    template<class T>
    int ArrayFind(const SArray<T> & array, const T & obj)
    {
        for(int i=0;i<(int)array.GetCount();i++)
        {
            if(array[i] == obj) return i;
        }
        return -1;
    }
}