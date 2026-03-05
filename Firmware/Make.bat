@echo off

if "%1==" goto :ERRORNOOUTPUT
if "%2==" goto :ERRORNOFILES

set C51TMP=C:\Temp
set C51INC=C:\C51\Inc
set C51LIB=C:\C51\Lib

set OUTPUT_FILE=%1
set OBJ_FILES=%2.obj

:LOOP

c:\C51\bin\c51 %2.c src small symbols
if errorlevel 1 goto :ERRORCOMPILE

c:\c51\bin\a51 %2.src EP(%2.err)
if errorlevel 1 goto :ERRORASSEMBLING

shift
if "%2==" goto :LINK

set OBJ_FILES=%OBJ_FILES%,%2.obj

goto :LOOP

:LINK

c:\C51\bin\L51 %OBJ_FILES%,c:\c51\lib\c51s.lib TO %OUTPUT_FILE%.obj map ramsize(256) xdata(8000h)
if errorlevel 2 goto :ERRORLINK

c:\C51\bin\OH51 %OUTPUT_FILE%.obj HEXFILE (%OUTPUT_FILE%.hex)
goto FINISH

:ERRORNOOUTPUT
echo.
echo Error: No output file given.
echo.
goto USAGE

:ERRORNOFILES
echo.
echo Error: No source files given.
echo.

:USAGE

echo "Usage: Make <outfile> <src_files>"
echo Note: No extensions.
echo.
goto FINISH

:ERRORCOMPILE
echo.
echo Error: compiling file %2.c.
echo.
goto FINISH

:ERRORASSEMBLING
echo.
echo Error: assembling file %2.src.
echo.
goto FINISH


:ERRORLINK
echo.
echo Error: linking file.
echo.
goto FINISH

:ABORT
echo.
echo Error.
echo.
:FINISH