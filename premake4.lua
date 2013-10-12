-- john solution.

solution "john"
  -- Release first so it is the default option
  configurations { "release", "debug" }
  platforms { "x64" }

  location "build"
   
  buildflags = { "-Wall", "-pedantic" }
   
  configuration { "debug" }
    defines { "DEBUG" }
    flags { "Symbols" }
    targetdir "bin/debug"
 
  configuration { "release" }
    defines { "NDEBUG" }
    flags { "Optimize" }
    targetdir "bin/release"

  configuration "macosx"
    linkoptions { "-std=c++11", "-stdlib=libc++" }
    buildoptions { "-std=c++11", "-stdlib=libc++" }

  configuration "vs*"
    defines { "__VS" }

  project "john"
    kind "ConsoleApp"
    language "C++"

    files { "src/**.cpp", "inc/**.h" }
    excludes { "src/test.cpp", "inc/test.h" }
    includedirs { "./inc" }

  project "test"
    kind "ConsoleApp"
    language "C++"

    files { "src/**.cpp", "inc/**.h" }
    excludes { "src/john.cpp", "inc/john.h" }
    includedirs { "./inc" }

-- a nice cleanup
if _ACTION == "clean" then
  os.rmdir("bin")
  os.rmdir("build")
end
