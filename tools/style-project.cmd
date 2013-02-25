@echo off
set TOOLSDIR=%~dp0
pushd "%~dp0"
cd ..
"%TOOLSDIR%astyle/bin/astyle.exe" -n "--options=%TOOLSDIR%astylerc" ^
  --recursive "osgTraits/*.h" ^
  --recursive "tests/*.h" ^
  --recursive "tests/*.cpp"
popd
