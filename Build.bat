@echo off
rem This is just a one-click file to run the vs2017 build script - Cleans then builds it again.
rem This will not work well with any of the files in use. It should announce that when cleaning.

echo -- [ CLEANING ] --
cd Build
call clean.bat

echo.
echo.
echo -- [ BUILDING ] --
cd Build
echo Building...
call build_vs2017.bat
cd ..

echo.
echo.
echo -- [ MOVING RESOURCES ] --
echo Note: Manual resource updates will need to be re-added with the batch file BuildResources.bat
echo Building...
call BuildResources.bat

echo.
echo.
echo -- [ EXITING ] --
timeout 30
