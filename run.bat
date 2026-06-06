@echo off
chcp 65001 > nul
setlocal

if not exist build mkdir build

echo Dang bien dich chuong trinh...

gcc --version > nul 2> nul
if %errorlevel%==0 (
    gcc -std=c11 -Wall -Wextra src\main.c src\utils.c src\data.c src\grade.c src\operations.c src\display.c src\file_io.c src\menu.c -o build\StudentManager.exe
    if errorlevel 1 goto build_error
    goto run_program
)

where cl > nul 2> nul
if errorlevel 1 (
    call :try_vcvars
)

where cl > nul 2> nul
if errorlevel 1 goto no_compiler

cl /nologo /TC /W3 /Fe:build\StudentManager.exe src\main.c src\utils.c src\data.c src\grade.c src\operations.c src\display.c src\file_io.c src\menu.c
if errorlevel 1 goto build_error

goto run_program

:try_vcvars
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" > nul
if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" > nul
if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" > nul
if exist "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" call "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" > nul
exit /b

:run_program
copy /Y input.txt build\input.txt > nul
cd build
echo.
echo Dang chay chuong trinh...
echo.
StudentManager.exe
cd ..
if exist build\output.txt copy /Y build\output.txt output.txt > nul
echo.
echo Neu chuong trinh da thoat, du lieu cuoi cung nam trong output.txt.
pause
exit /b

:no_compiler
echo Khong tim thay trinh bien dich C.
echo Cach 1: Cai MinGW-w64 va them gcc vao PATH.
echo Cach 2: Cai Visual Studio voi Desktop development with C++, roi chay lai file nay.
pause
exit /b 1

:build_error
echo Bien dich loi. Hay chup man hinh loi gui cho ChatGPT.
pause
exit /b 1
