@REM CALL "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 -vcvars_ver=14.2
@REM cd /d C:\Users\nobod\Documents\3dsMaxPluginTest\3dsMax-Learning-Path\Lesson1a

rmdir /s /q build_hybrid
cmake -S . -B build_hybrid -G "Visual Studio 17 2022" -A x64 -T v142
@REM cmake --build build_hybrid --config Hybrid
cmake --build build_hybrid --config Release