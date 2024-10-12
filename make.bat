@echo off
echo Building project...

if exist build (
    rmdir /S /Q build
    echo Previous build files cleaned.
)

mkdir build
cd build

where conan >nul 2>&1
if %errorlevel% neq 0 (
    echo "Conan n'est pas installé. Veuillez l'installer avant de continuer."
    exit /b 1
)

cmake .. 

conan install .. --build=missing
cmake --build . --config Release

echo Build complete!
pause
