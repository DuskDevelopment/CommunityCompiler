@echo off

if not defined DEV_ENV_DIR (
    echo Setting up vcvarsall.bat
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
)
set DEV_ENV_DIR= ???

IF NOT EXIST "build" mkdir "build"

echo starting build
pushd build
cl -nologo -MDd -Od -Zi -Feduskc.exe ..\src\main.c
popd