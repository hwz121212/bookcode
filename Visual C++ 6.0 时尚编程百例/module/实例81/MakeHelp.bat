@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by NOVEL.HPJ. >"hlp\novel.hm"
echo. >>"hlp\novel.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\novel.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\novel.hm"
echo. >>"hlp\novel.hm"
echo // Prompts (IDP_*) >>"hlp\novel.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\novel.hm"
echo. >>"hlp\novel.hm"
echo // Resources (IDR_*) >>"hlp\novel.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\novel.hm"
echo. >>"hlp\novel.hm"
echo // Dialogs (IDD_*) >>"hlp\novel.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\novel.hm"
echo. >>"hlp\novel.hm"
echo // Frame Controls (IDW_*) >>"hlp\novel.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\novel.hm"
REM -- Make help for Project NOVEL


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\novel.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\novel.hlp" goto :Error
if not exist "hlp\novel.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\novel.hlp" Debug
if exist Debug\nul copy "hlp\novel.cnt" Debug
if exist Release\nul copy "hlp\novel.hlp" Release
if exist Release\nul copy "hlp\novel.cnt" Release
echo.
goto :done

:Error
echo hlp\novel.hpj(1) : error: Problem encountered creating help file

:done
echo.
