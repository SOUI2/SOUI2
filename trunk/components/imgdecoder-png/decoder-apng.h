#pragma once

struct FRAME { 
    BYTE * p;       //ȫ��ͼƬ����
    LPBYTE * rows;  //ÿһ�еĿ�ʼλ�ã��ж�֡ʱ��˳��������
};

class APNGDATA
{
public:
    APNGDATA()
    {
        frame.p = NULL;
        frame.rows = NULL;
        pDelay =NULL;
        nWid = nHei =nFrames = nLoops =0;
    }

    ~APNGDATA()
    {
        if(frame.p) delete []frame.p;
        if(frame.rows) delete []frame.rows;
        if(pDelay) delete []pDelay;
    }

    FRAME frame;
    unsigned short *pDelay;
    int   nWid,nHei;
    int   nFrames;
    int   nLoops;
};

APNGDATA * LoadAPNG_from_file(LPCWSTR pszFileName);

APNGDATA * LoadAPNG_from_memory(char * pBuf, int nLen);
