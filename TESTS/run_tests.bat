@echo off
setlocal
cd /d "%~dp0"

echo Dang bien dich Unit Tests...
gcc -g -Wall src/test_main.c src/test_utils.c src/test_grade.c src/test_data.c ../SRC/utils.c ../SRC/grade.c ../SRC/data.c -I ../SRC -o build/test_runner.exe

if %ERRORLEVEL% NEQ 0 (
    echo [LOI] Bien dich that bai! Kiem tra lai ma nguon C.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Bien dich thanh cong! Chay Test...
echo ==============================================
build\test_runner.exe
echo ==============================================
pause
