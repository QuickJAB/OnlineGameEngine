@echo off
setlocal ENABLEDELAYEDEXPANSION

REM === Check for CMake ===
where cmake >nul 2>&1
if errorlevel 1 (
    echo ERROR: CMake is not installed or not in PATH.
    pause
    exit /b 1
)

REM === Check for Premake5 ===
where premake5 >nul 2>&1
if errorlevel 1 (
    echo ERROR: Premake5 is not installed or not in PATH.
    pause
    exit /b 1
)

REM === Create extern directory ===
if not exist extern mkdir extern

REM ======================
REM === SDL3
REM ======================
echo Cloning SDL3...
if not exist extern\SDL (
    git clone https://github.com/libsdl-org/SDL.git extern\SDL
) else (
    echo SDL3 already cloned.
)

echo Building SDL3 (Debug and Release)...
mkdir extern\SDL\build >nul 2>&1
cd extern\SDL\build

cmake .. -DSDL_TEST=OFF -DCMAKE_INSTALL_PREFIX=..\install

cmake --build . --config Debug
cmake --install . --config Debug

cmake --build . --config Release
cmake --install . --config Release

cd ..\..\..

REM ======================
REM === stb_truetype
REM ======================
echo Downloading stb_truetype...
if not exist extern\stb mkdir extern\stb
curl -L -o extern\stb\stb_truetype.h https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h

REM ======================
REM === ENet
REM ======================
echo Cloning ENet...
if not exist extern\enet (
    git clone https://github.com/lsalzman/enet.git extern\enet
) else (
    echo ENet already cloned.
)

echo Building ENet (Debug and Release)...
mkdir extern\enet\build >nul 2>&1
cd extern\enet\build

cmake .. -DCMAKE_INSTALL_PREFIX=..\install

cmake --build . --config Debug
cmake --install . --config Debug

cmake --build . --config Release
cmake --install . --config Release

cd ..\..\..

REM ======================
REM === Generate Projects
REM ======================
echo Generating Visual Studio project files with Premake...
premake5 vs2022

echo.
echo Setup complete! You can now open the solution and build.
pause