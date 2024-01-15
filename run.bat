@echo off
setlocal enableextensions enabledelayedexpansion
set Cfiles=
set Cfiles=%Cfiles% .\lib\glad\src\glad_gl.o
for /R .\src %%f in (*) do (
    if %%~xf==.c set "Cfiles=!Cfiles! %%f"
)
gcc -Wall -I./lib/glad/include -I./lib/ht/include -I./lib/glfw/include -I./lib/stb/include -L./lib/glfw/link %Cfiles% -lglfw3dll -o prog
prog