@ECHO off
SETLOCAL enabledelayedexpansion
cls
COLOR 1f

ECHO.
ECHO.
ECHO   ##############################################################
ECHO   #               ~{;6S-J9SC~} SOUI ~{9$3LEdVCOr5<~}                   #
ECHO   #                                ~{Ft3LHm<~~} 2014.10.31         #
ECHO   ##############################################################
ECHO.
ECHO.

SET cfg=
SET specs=
SET target=x86
SET selected=
rem ~{Q!Tq1`Rk0f1>~}
SET /p selected=1.~{Q!Tq1`Rk0f1>~}[1=x86;2=x64]:
if %selected%==1 (
	SET target=x86
) else if %selected%==2 (
	SET target=x64
	SET cfg=!cfg! x64
) else (
	goto error
)

rem ~{Q!Tq?*7";7>3~}
SET /p selected=2.~{Q!Tq?*7";7>3~}[1=vs2008;2=vs2010;3=vs2012;4=vs2013]:
if %selected%==1 (
	SET specs=win32-msvc2008
	call "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==2 (
	SET specs=win32-msvc2010
	call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==3 (
	SET specs=win32-msvc2010
	call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==4 (
	SET specs=win32-msvc2010
	call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else (
	goto error
)

rem ~{Q!Tq1`Rk@`PM~}
SET /p selected=3.~{Q!Tq~}SOUI~{1`RkD#J=~}[1=~{H+D#?i~}DLL;2=~{H+D#?i~}LIB;3=~{DZ:K~}LIB,~{Wi<~~}DLL(~{2;D\J9SC~}LUA~{=E1>D#?i~})]:
if %selected%==1 (
	rem do nothing
) else if %selected%==2 (
	SET cfg=!cfg! LIB_ALL
) else if %selected%==3 (
	SET cfg=!cfg! CORE_LIB
) else (
	goto error
)

rem ~{Q!TqWV7{</~}
SET /p selected=4.~{Q!TqWV7{</~}[1=UNICODE;2=MBCS]:
if %selected%==1 (
	rem do nothing
) else if %selected%==2 (
	SET cfg=!cfg! MBCS
) else (
	goto error
)

rem CLR
rem SET /p selected=5.~{Q!Tq~}CLR~{?*9X~}[1=~{2;V'3V~};2=~{V'3V~}]:
rem if %selected%==1 (
rem 	rem do nothing
rem ) else if %selected%==2 (
rem 	SET cfg=!cfg! USING_CLR
rem ) else (
rem 	goto error
rem )

rem CRT
SET /p selected=6.~{Q!Tq~}CRT~{A4=SD#J=~}[1=~{>2L,A4=S~}(MT);2=~{6/L,A4=S~}(MD)]:
if %selected%==1 (
	SET cfg=!cfg! USING_MT
) else if %selected%==2 (
	rem do nothing
) else (
	goto error
)

rem ~{N*~}release~{0f1>Iz3I5wJTPEO"~}
SET /p selected=7.~{JG7qN*~}release~{0f1>Iz3I5wJTPEO"~}[1=~{Iz3I~};2=~{2;Iz3I~}]:
if %selected%==1 (
	SET cfg=!cfg! CAN_DEBUG
) else if %selected%==2 (
	rem do nothing
) else (
	goto error
)

rem ~{2NJ}EdVCMj3I~}

tools\qmake -tp vc -r -spec .\tools\mkspecs\%specs% "CONFIG += %cfg%"

SET /p selected=open[o], compile[c] "soui.sln" or quit(q) [o,c or q]?
if "%selected%" == "o" (
	soui.sln
) else if "%selected%" == "c" (
	call devenv soui.sln /Clean Debug
	call devenv soui.sln /build Debug
	call devenv soui.sln /Clean Release
	call devenv soui.sln /build Release
) else (
	goto final
)

goto final

:error
	ECHO ~{Q!Tq4mNs#,GkVXPBQ!Tq~}

:final


















rem pause