@echo off
setlocal

:: Define Generator
set "GENERATOR=NMake Makefiles"
set "GENERATOR_COMMAND=nmake"

:: Define the build folder
set "BUILD_DIR=build" 

:: Remove current build folder if it exists
if exists "%BUILD_DIR%" (
  echo Deleting existing build directory...
  rmdir /S /Q "%BUILD_DIR%"
)

:: Create build directory
echo Creating new build directory (%BUILD_DIR%)...
mkdir "%BUILD_DIR%"

:: Change to the build directory
cd "%BUILD_DIR%"

:: Run CMake
echo Generating source with generator: %GENERATOR%...
cmake .. -G "%GENERATOR%"

:: Run the generator
echo Compiling project with: %GENERATOR_COMMAND%...
%GENERATOR%

endlocal
