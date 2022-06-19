@echo off
REM set this run on system boot
REM please run this script as administrator authorization
reg add HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run /v WallnoteService2 /t reg_sz /d "%~dp0wallnote.exe"
@start %~dp0wallnote.exe
@exit