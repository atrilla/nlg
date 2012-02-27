solution "nlg"
    configurations { "debug", "release" }

project "nlg"
    kind "ConsoleApp"
    language "C++"
    -- Includes
    includedirs { "include" }
    -- Sources
    files { "src/**.cpp" }
    -- Libraries
    libdirs { os.findlib("boost_iostreams") }
    links { "boost_iostreams" }

    configuration "debug"
        defines { "DEBUG" }
        flags { "Symbols" }
        targetdir "bin/debug"

    configuration "release"
        defines { "NDEBUG" }
        flags { "Optimize" }
        targetdir "bin/release"

