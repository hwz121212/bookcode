@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX11D.HPJ. >"hlp\ex11d.hm"
echo. >>"hlp\ex11d.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ex11d.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ex11d.hm"
echo. >>"hlp\ex11d.hm"
echo // Prompts (IDP_*) >>"hlp\ex11d.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ex11d.hm"
echo. >>"hlp\ex11d.hm"
echo // Resources (IDR_*) >>"hlp\ex11d.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ex11d.hm"
echo. >>"hlp\ex11d.hm"
echo // Dialogs (IDD_*) >>"hlp\ex11d.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ex11d.hm"
echo. >>"hlp\ex11d.hm"
echo // Frame Controls (IDW_*) >>"hlp\ex11d.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ex11d.hm"
REM -- Make help for Project EX11D


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ex11d.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ex11d.hlp" goto :Error
if not exist "hlp\ex11d.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ex11d.hlp" Debug
if exist Debug\nul copy "hlp\ex11d.cnt" Debug
if exist Release\nul copy "hlp\ex11d.hlp" Release
if exist Release\nul copy "hlp\ex11d.cnt" Release
echo.
goto :done

:Error
echo hlp\ex11d.hpj(1) : error: Problem encountered creating help file

:done
echo.
