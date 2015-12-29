@echo off

set PATH=%APPDATA%\npm;%~dp0;%PATH%
cd C:\Program Files\pd

start rundll32.exe user32.dll, LockWorkStation

:loop
bin\pd.exe -nosleep -font-face "Lucida Console" C:\Users\Administrator\Elevator\pd\elevator.pd
goto loop