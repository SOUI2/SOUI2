rem DLL_SOUI ָʾΪSOUI����DLL�汾��
rem USING_MT ָʾ������Ŀʹ��MT��ʽ����CRT
rem CAN_DEBUG ָʾΪ���ɵ�Release�汾�������Է���
call "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat" x64
tools\qmake -tp vc -r -spec .\tools\mkspecs\win32-msvc2008 "CONFIG += DLL_SOUI USING_MT CAN_DEBUG x64"
rem soui.sln