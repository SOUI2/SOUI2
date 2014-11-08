#pragma once

// DISALLOW_COPY_AND_ASSIGN���ÿ����͸�ֵ���캯��.
// ��Ҫ�����private:���ʿ�������ʹ��.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((int)(short)HIWORD(lParam))
#endif


#ifdef _DISABLE_NO_VTABLE
#define S_NO_VTABLE
#else
#define S_NO_VTABLE __declspec(novtable)
#endif


// SWindow Handle
typedef DWORD SWND;
typedef ULONG_PTR HSTREEITEM;
