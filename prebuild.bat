@echo off
echo Detecting package manager...

set package_manager=

where choco >nul 2>&1
if %errorlevel% equ 0 (
    set package_manager=choco
)

where winget >nul 2>&1
if %errorlevel% equ 0 (
    set package_manager=winget
)

where scoop >nul 2>&1
if %errorlevel% equ 0 (
    set package_manager=scoop
)

if "%package_manager%"=="" (
    echo No supported package manager found. Please install Conan and CMake manually.
    exit /b 84
)

echo %package_manager% detected.

if "%package_manager%"=="choco" (
    echo Installing with Chocolatey...
    choco install -y gcc cmake boost conan
) else if "%package_manager%"=="winget" (
    echo Installing with Winget...
    winget install -e --id Kitware.CMake
    winget install -e --id Boost.Boost
    winget install -e --id Conan.CLI
) else if "%package_manager%"=="scoop" (
    echo Installing with Scoop...
    scoop install gcc cmake boost conan
)

echo Configuring Conan...
conan profile detect
conan profile update settings.compiler.libcxx=libstdc++11 default
echo Conan is now configured.

cd C:\Users\HP\Documents\B-CPP-500-COT-5-1-rtype-yann-meric.sossou

cmake . 
cmake --build . -- -j2

echo Build complete!
pause
