# john 
## A C++ ray tracer

john is cross platfrom ray tracer written in C++.

# Compiling
You will need premake to compile john. Premake will generate build files for
Visual Studio, GNU makefiles, CodeLite, Code::Blocks, and Xcode 3.

## On Windows with Visual Studio 2010 (and 2012)
Use premake4 to create the project solution.

    premake4 vs2010

Open the solution in build/ and compile.


## On Linux with gmake

    premake4 gmake
    cd build
    make
