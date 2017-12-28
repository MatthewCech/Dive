::@echo off
echo.
IF EXIST project_vs2017 (
  xcopy Resources .\project_vs2017\Resources\ /s
)
timeout 2