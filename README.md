# john - a c++ ray tracer
john is cross platform ray tracer written in C++, with some C++11 features.

## Prerequisites
None really, although premake4 will make the build process far easier. ;)

## Compiling
You can use premake to create the project files for john.

### On Windows with Visual Studio 2010 (and 2012)
Use premake4 to create the project solution.

    premake4 vs2010

Open the solution in build/ and compile or,

    msbuild build\john.sln /nologo /m /p:Configuration=Debug

### On Linux

    premake4 gmake
    cd build
    make
