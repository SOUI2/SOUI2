/****************************************************************************
*  ��    �ܣ���Ƶ�ļ�������                                                 *
*  �� �� �ˣ�С��                                                           *
*  ���ʱ�䣺2014.01.17 12��27                                              *
*  �汾���ͣ���ʼ�汾                                                       *
*  ��ϵ��ʽ��QQ-1035144170                                                  *
****************************************************************************/

#pragma once
#include "DropEx.h"
#include "BassMusic.h"

class CMusicOpreat:public IMusicState,public SHostWnd
{
public:
	CMusicOpreat(void);
	~CMusicOpreat(void);

	static CMusicOpreat *GetInstance();

	//�ӿڼ̳�
public:
	//���ڲ���
	virtual void OnPlaying(){}
	//��ͣ״̬
	virtual void OnPause(){}
	//ֹͣ����
	virtual void OnStop();
	//��/�� �ٲ���
	virtual void OnStalled(){}

	//�Զ���
public:
	int                 nIndex;         //��������
	HSTREAM             hStream;        //������
	CMusicManagerMap	m_MusicManager;
	CBassMusicEngine    *m_pBassMusic;
	IMusicState			*m_pMainState;
	
	void InitDatas();
	void OnButPrev();
	void OnButPlay();
	void OnButPause();
	void OnButPlayNext();

	void InsertMapInfo(int nNum, CString strPath, tagMusicInfo &pMuInfo);
};