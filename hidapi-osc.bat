@echo off

set PATH=%APPDATA%\npm;%~dp0;%PATH%
cd C:\Users\Administrator\Elevator\hidapi-osc

:loop
.\hidapi-osc.exe localhost 7000
goto loop