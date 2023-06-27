@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX21B.HPJ. >"hlp\ex21b.hm"
echo. >>"hlp\ex21b.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ex21b.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ex21b.hm"
echo. >>"hlp\ex21b.hm"
echo // Prompts (IDP_*) >>"hlp\ex21b.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ex21b.hm"
echo. >>"hlp\ex21b.hm"
echo // Resources (IDR_*) >>"hlp\ex21b.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ex21b.hm"
echo. >>"hlp\ex21b.hm"
echo // Dialogs (IDD_*) >>"hlp\ex21b.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ex21b.hm"
echo. >>"hlp\ex21b.hm"
echo // Frame Controls (IDW_*) >>"hlp\ex21b.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ex21b.hm"
REM -- Make help for Project EX21B


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ex21b.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ex21b.hlp" goto :Error
if not exist "hlp\ex21b.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ex21b.hlp" Debug
if exist Debug\nul copy "hlp\ex21b.cnt" Debug
if exist Release\nul copy "hlp\ex21b.hlp" Release
if exist Release\nul copy "hlp\ex21b.cnt" Release
echo.
goto :done

:Error
echo hlp\ex21b.hpj(1) : error: Problem encountered creating help file

:done
echo.
