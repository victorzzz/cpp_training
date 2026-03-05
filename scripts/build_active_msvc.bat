@echo off
setlocal

if "%~1"=="" (
  echo Usage: build_active_msvc.bat ^<path-to-cpp-file^>
  exit /b 1
)

set "SRC=%~1"
set "OUT=%~dpn1.exe"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

if not exist "%VSWHERE%" (
  echo Could not find vswhere.exe. Install Visual Studio 2022 or Build Tools with C++ workload.
  exit /b 1
)

for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
  set "VSINSTALL=%%i"
)

if "%VSINSTALL%"=="" (
  echo Could not find a Visual Studio installation with MSVC tools.
  exit /b 1
)

call "%VSINSTALL%\Common7\Tools\VsDevCmd.bat" -arch=x64 >nul
if errorlevel 1 (
  echo Failed to initialize MSVC developer environment.
  exit /b 1
)

cl /nologo /std:c++20 /EHsc /W4 /Zi "%SRC%" /Fe:"%OUT%"
exit /b %ERRORLEVEL%
