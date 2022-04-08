@echo off

mkdir final-win64
cd final-win64
cmake -G "Visual Studio 17 2022" ../../src/ga1-core
cd ..
