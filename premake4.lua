-- john solution.

if _ACTION == "clean" then
  os.rmdir("bin")
  os.rmdir("build")
end

solution "john"
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
   
	buildflags = { "fatal-warnings" }
   
	location "build"
	targetdir "bin"
   
	configuration { "Debug" }
		defines { "DEBUG" }
		flags { "Symbols" }
		targetdir ( "bin/debug" )
 
	configuration { "Release" }
		defines { "NDEBUG" }
		flags { "Optimize" }
		targetdir ( "bin/release" )
   
	project "john"
		kind "ConsoleApp"
		language "C++"
		files { "src/**", "inc/**" }
	    includedirs { "./inc" }
