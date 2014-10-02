#pragma once

struct FRAME { 
    BYTE * p;       //ȫ��ͼƬ����
    LPBYTE * rows;  //ÿһ�еĿ�ʼλ�ã��ж�֡ʱ��˳��������
};

class APNGDATA
{
public:
    APNGDATA();

    ~APNGDATA();

    FRAME frame;
    unsigned short *pDelay;
    int   nWid,nHei;
    int   nFrames;
    int   nLoops;
};

APNGDATA * LoadAPNG_from_file(LPCWSTR pszFileName);

APNGDATA * LoadAPNG_from_memory(char * pBuf, int nLen);
