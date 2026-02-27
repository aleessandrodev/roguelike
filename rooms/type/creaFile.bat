@echo off
set /p count=Quanti file vuoi creare? 
set /p type=Inserisci il tipo (prefisso) dei file: 

set i=0

:loop
if %i% GEQ %count% goto end

type nul > "%type%%i%.txt"

set /a i=%i%+1
goto loop

:end
echo Creati %count% file.
pause
