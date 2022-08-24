@echo off
REM set this run on system boot
REM please run this script as administrator authorization


REM System boot HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
REM User boot HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
REM current machine boot  HKLM\SYSTEM\CurentControl\Session Manager
REM new User boot  HKU\DEFAULT\SOFTWARE\Microsoft\Windows\CurrentVersion\Run

reg add HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run /v WallnoteService2 /t reg_sz /d "%~dp0wallnote.exe"
@start %~dp0wallnote.exe
@exit