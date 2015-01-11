#include <shellapi.h>
#include <windows.h>
#define FILEILTER _T("*.*")
#include "atlstr.h"//ʹ��CString������
#include "BassMusic.h"

typedef map<int,tagMusicInfo*>	CMusicManagerMap;

class CTestDropTarget:public IDropTarget
{
public:
	CTestDropTarget()
	{
		nRef=0;
	}

	virtual ~CTestDropTarget(){}

public:

	//////////////////////////////////////////////////////////////////////////
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		HRESULT hr=S_FALSE;
		if(riid==__uuidof(IUnknown))
			*ppvObject=(IUnknown*) this,hr=S_OK;
		else if(riid==__uuidof(IDropTarget))
			*ppvObject=(IDropTarget*)this,hr=S_OK;
		if(SUCCEEDED(hr)) AddRef();
		return hr;

	}

	virtual ULONG STDMETHODCALLTYPE AddRef( void){return ++nRef;}

	virtual ULONG STDMETHODCALLTYPE Release( void) { 
		ULONG uRet= -- nRef;
		if(uRet==0) delete this;
		return uRet;
	}

	//////////////////////////////////////////////////////////////////////////
	// IDropTarget

	virtual HRESULT STDMETHODCALLTYPE DragEnter( 
		/* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
		/* [in] */ DWORD grfKeyState,
		/* [in] */ POINTL pt,
		/* [out][in] */ __RPC__inout DWORD *pdwEffect)
	{
		*pdwEffect=DROPEFFECT_LINK;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE DragOver( 
		/* [in] */ DWORD grfKeyState,
		/* [in] */ POINTL pt,
		/* [out][in] */ __RPC__inout DWORD *pdwEffect)
	{
		*pdwEffect=DROPEFFECT_LINK;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE DragLeave( void)
	{
		return S_OK;
	}


protected:
	int nRef;
};

class CTestDropTarget1 : public CTestDropTarget
{
protected:
	SWindow *m_pEdit;
public:
	CTestDropTarget1(SWindow *pEdit):m_pEdit(pEdit)
	{
		if(m_pEdit) m_pEdit->AddRef();
	}
	~CTestDropTarget1()
	{
		if(m_pEdit) m_pEdit->Release();
	}

public:
	virtual HRESULT STDMETHODCALLTYPE Drop( 
		/* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
		/* [in] */ DWORD grfKeyState,
		/* [in] */ POINTL pt,
		/* [out][in] */ __RPC__inout DWORD *pdwEffect)
	{
		FORMATETC format =
		{
			CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL
		};
		STGMEDIUM medium;
		if(FAILED(pDataObj->GetData(&format, &medium)))
		{
			return S_FALSE;
		}

		//HDROP hdrop = static_cast<HDROP>(GlobalLock(medium.hGlobal));
		HDROP hdrop = static_cast<HDROP>(medium.hGlobal);

		if(!hdrop)
		{
			return S_FALSE;
		}

		//bool success = false;
		//TCHAR filename[MAX_PATH];
		//success=!!DragQueryFile(hdrop, 0, filename, MAX_PATH);
		//DragFinish(hdrop);


		UINT count;          
		TCHAR filePath[MAX_PATH];
		count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);          
		if(count)           
		{
			for(UINT i=0; i<count; i++)                    
			{
				int pathLen = DragQueryFile(hdrop, i, filePath, sizeof(filePath));                             
				CString str= filePath;
				str.Format(_T("%s"), filePath);
				int filetype;
				filetype=IsWantedFile(filePath);
				if (1==filetype) //��Ƶ��ʽ
				{
					int i=0;
					//MessageBox(_T("��Ҫ���ŵ�����Ƶ�ļ�������")); 
				}
				if (0==filetype) //��Ƶ��ʽ
				{
					int i=0;
					//MessageBox(_T("��Ҫ���ŵ�����Ƶ�ļ�������")); 

				}
				if (-1==filetype)//������ʽ
				{
					int i=0;
					//MessageBox(_T("����֧�ֵ��ļ���ʽ����������ק��*.mp3;*.wma;*.wav;*.mid;*.rmi;*.aac;*.ac3;*.aiff;*.m4a;*.mka;*.mp2;*.ogg��*.rm;*.rmvb;*.flv;*.f4v;*.avi;*.3gp;*.mp4;*.wmv;*.mpeg;*.mpga;*.asf;*.dat;*.mov��������Ƶ�ļ���")); 
				}
				TraverseFolder(filePath);
				FindInAll(filePath);
				//���ж����ļ������ļ����ٱ���
				//if ()//�����ļ�
				//{
				//}else//�ļ���
				//{
				//}
				//m_PicCtr.push_back(filePath);
				//BrowerFolder(filePath,0);
				if(count && m_pEdit)
				{
					m_pEdit->SetWindowText(filePath);
				}

			}
		}
		DragFinish(hdrop); 
		//GlobalUnlock(medium.hGlobal);

		*pdwEffect=DROPEFFECT_LINK;
		return S_OK;
	}

	/***********************************************************************
	*  �� �� ����IsWantedFile                                          
	*  ��������: �ж��Ƿ�����Ҫ���ļ�                                         
	*  ���������const CString &str       [IN] :������Ƶ�ļ�·��      
	*  �������: ��
	*  �� �� ֵ��TRUE ִ�гɹ�
	* 		     HKL_DLL_FAILU ִ��ʧ��
	*  �׳��쳣����
	***********************************************************************/
	BOOL IsWantedFile(const CString &str)
	{
		CString strLower;
		TCHAR   szExt[_MAX_EXT] = _T("");
		int videoType = 0;//�ж��Ƿ���ϵ���Ƶ�ļ����
		int musicType = 0;//�ж��Ƿ���ϵ���Ƶ�ļ����

		// ����͵��ֱ������֮ǰ�Ĺ����ַ����������ļ������ܺ��С�*�������Կ����ں�׺��������ϡ�;*�����ж��Ƿ���ȫƥ��
		const   CString Video_FileFilter =
			_T("*.rm;*.rmvb;*.flv;*.f4v;*.avi;*.3gp;*.mp4;*.wmv;*.mpeg;*.mpga;*.asf;*.dat;*.mov;*");
		const   CString Music_FileFilter =
			_T("*.mp3;*.wma;*.wav;*.mid;*.rmi;*.aac;*.ac3;*.aiff;*.m4a;*.mka;*.mp2;*.ogg;*");

		_tsplitpath_s(str, NULL, 0, NULL, 0, NULL, 0, szExt, _MAX_EXT);   // ��ȡ��׺��
		strLower = szExt;
		strLower.MakeLower();

		if(! strLower.IsEmpty())    // û�к�׺���Ĳ���������
		{
			strLower += _T(";*");   // .mo���������������ڻ�ƥ�䵽.mov�������ں�����ϡ�;*�����ж��Ƿ���ȫƥ��
			videoType = Video_FileFilter.Find(strLower);
			musicType = Music_FileFilter.Find(strLower);
			//���������жϣ�����1����Ƶ������0����Ƶ������-1�����ϵĺ�׺��ʽ
			if (videoType>0)
			{
				return 1;
			}
			if (musicType>0)
			{
				return 0;
			}
			if (videoType<0||musicType<0)
			{
				return -1;
			}
			//return -1 != STR_FileFilter.Find(strLower);
		}
		return FALSE;
	}

	/***********************************************************************
	*  �� �� ����FindInAll                                          
	*  ��������: �����ļ��к���                                         
	*  ���������LPCTSTR lpPath      [IN] :�ļ���·��      
	*  �������: ��
	*  �� �� ֵ����
	*  �׳��쳣����
	***********************************************************************/
	void TraverseFolder(LPCTSTR lpPath)
	{
		TCHAR szFind[MAX_PATH] = {_T("\0")};
		WIN32_FIND_DATA findFileData;
		BOOL bRet;

		_tcscpy_s(szFind, MAX_PATH, lpPath);
		_tcscat_s(szFind, _T("\\*.*"));     //����һ��Ҫָ��ͨ�������Ȼ�����ȡ�����ļ���Ŀ¼

		HANDLE hFind = ::FindFirstFile(szFind, &findFileData);
		if (INVALID_HANDLE_VALUE == hFind)
		{
			return;
		}

		//�����ļ���
		while (TRUE)
		{
			if (findFileData.cFileName[0] != _T('.'))
			{
				//���ǵ�ǰ·�����߸�Ŀ¼�Ŀ�ݷ�ʽ
				_tprintf(_T("%s\\%s\n"), lpPath, findFileData.cFileName);
				if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//����һ����ͨĿ¼

					//������һ����Ҫɨ����ļ���·��
					_tcscpy_s(szFind, MAX_PATH, lpPath);    
					_tcscat_s(szFind, _T("\\"));    
					_tcscat_s(szFind, findFileData.cFileName);
					///_tcscat_s(szNextDir, _T("\\*"));
					//������Ŀ¼
					TraverseFolder(szFind);
				}

			}

			//����ǵ�ǰ·�����߸�Ŀ¼�Ŀ�ݷ�ʽ����������ͨĿ¼����Ѱ����һ��Ŀ¼�����ļ�
			bRet = ::FindNextFile(hFind, &findFileData);
			if (!bRet)
			{
				//��������ʧ��

				//cout << "FindNextFile failed, error code: " 

				//  << GetLastError() << endl;
				break;
			}
		}
		::FindClose(hFind);
	}

	/***********************************************************************
	*  �� �� ����FindInAll                                          
	*  ��������: ���������ļ�                                         
	*  ���������LPCTSTR lpszPath       [IN] :�ļ���·��      
	*  �������: ��
	*  �� �� ֵ����
	*  �׳��쳣����
	***********************************************************************/
	void FindInAll(LPCTSTR lpszPath) 
	{    
		TCHAR szFind[MAX_PATH];     
		lstrcpy(szFind, lpszPath);     
		if (!IsRoot(szFind))         
			lstrcat(szFind, _T("\\"));     
		lstrcat(szFind, FILEILTER); 
		// �������ļ�     
		WIN32_FIND_DATA wfd;     
		HANDLE hFind = FindFirstFile(szFind, &wfd);     
		if (hFind == INVALID_HANDLE_VALUE) // ���û���ҵ������ʧ��         
			return;          
		do     
		{         
			if (wfd.cFileName[0] == '.')             
				continue; // ����������Ŀ¼         
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)         
			{             
				TCHAR szFile[MAX_PATH];             
				if (IsRoot(lpszPath))                 
					wsprintf(szFile, _T("%s%s"), lpszPath, wfd.cFileName);            
				else             
				{
					wsprintf(szFile, _T("%s\\%s"), lpszPath, wfd.cFileName);                 
					FindInAll(szFile); // ����ҵ�����Ŀ¼��������Ŀ¼���еݹ�             
				}       
			}        
			else         
			{             
				TCHAR szFile[MAX_PATH];             
				if (IsRoot(lpszPath))             
				{                
					wsprintf(szFile, _T("%s%s"), lpszPath, wfd.cFileName);             
				}           
				else             
				{                
					wsprintf(szFile, _T("%s\\%s"), lpszPath, wfd.cFileName);               
					printf("%s\n",szFile);  
					InsertMusicMap(szFile);
				}// ���ļ����в���         
			}     
		}
		while (FindNextFile(hFind, &wfd));     
		FindClose(hFind); // �رղ��Ҿ��      
	} 

	BOOL IsRoot(LPCTSTR lpszPath) 
	{     
		TCHAR szRoot[4];     
		wsprintf(szRoot, _T("%c:\\"), lpszPath[0]);     
		return (lstrcmp(szRoot, lpszPath) == 0); 
	} 
	//int main(int argc, char* argv[]) {     char findFile[64]="d:";//Ҫ���ҵ�Ŀ¼    FindInAll(findFile);    getchar();    return 0; } 

	void InsertMusicMap( LPCTSTR lpFilePath )
	{
		//������ק���ļ�����Ƶ���������
		int i=0;
		////�����ļ�
		//HSTREAM hStream = m_pBassMusic->LoadFile(lpFilePath);
		//if ( hStream == -1 ) return;

		////��ListBox�����������
		////m_ListMusic.AddString(lpFileName);

		////��ȡý���ǩ
		//tagMusicInfo *pInfo = m_pBassMusic->GetInfo(hStream);

		////ͨ��map��ListBox��ϣ�һ��������б�
		//tagMusicInfo *pMusicInfo = new tagMusicInfo;

		//pMusicInfo->dwTime = pInfo->dwTime;
		//pMusicInfo->hStream = pInfo->hStream;
		//lstrcpyn(pMusicInfo->szArtist,pInfo->szArtist,CountArray(pMusicInfo->szArtist));
		//lstrcpyn(pMusicInfo->szTitle,pInfo->szTitle,CountArray(pMusicInfo->szTitle));

		//m_MusicManager.insert(pair<int,tagMusicInfo*>(1,pMusicInfo));
	}

};

