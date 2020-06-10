if _ACTION == "clean" then
    -- generated binaries
    os.remove("bin/mk1-d32.exe"); os.remove("bin/mk1-d64.exe");
    os.remove("bin/mk1-d32"); os.remove("bin/mk1-d64");
    os.remove("bin/mk1-r32.exe"); os.remove("bin/mk1-r64.exe");
    os.remove("bin/mk1-r32"); os.remove("bin/mk1-r64");

    -- crash dumps
    os.remove("bin/crash.dmp")

    -- visual studio files
    os.remove("mk1.sdf")
    os.remove("mk1.v14.suo")
    os.rmdir("ipch")

    -- xcode
    os.rmdir("mk1.xcworkspace")

    os.rmdir("build")
    os.rmdir("docs")
end

GCC_BUILD_OPTS = { -- also clang
    "-Wall",
    "-pedantic",
    "-Wextra",

    "-Wcast-align",
    "-Wcast-qual",
    "-Wconversion",
    "-Wdisabled-optimization",
    "-Wfloat-equal",
    "-Wformat-nonliteral",
    "-Wformat-security",
    "-Wformat-y2k",
    "-Wformat=2",
    "-Wimport",
    "-Winit-self",
    "-Winvalid-pch",
    "-Wmissing-field-initializers",
    "-Wmissing-format-attribute",
    "-Wmissing-include-dirs",
--    "-Wmissing-noreturn", -- disabled for libfmt
    "-Wpacked",
    "-Wredundant-decls",
    "-Wstack-protector",
    "-Wno-unknown-pragmas",
}

function popen_result(command)
    local f = assert(io.popen(command))
    local out = f:read("*all");
    f:close()

    return out:gsub('^%s+', ''):gsub('%s+$', ''):gsub('[\n\r]+', ' ')
end

MSVC_BUILD_OPTS = {
    "/wd4351", -- "elements of array will be default initialized"
    "/wd4800", -- "forcing value to bool"
    "/wd4996", -- ms declared deprecated standard c functions
    "/GF",     -- pool strings
    "/sdl",    -- security development lifecycle recommended checks
}

solution "mk1"
    configurations { "Release", "Debug" }
    platforms { "x64", "x32" }
    flags { "CppLatest", "EnableSSE2", "FloatFast", "NoNativeWChar", "Symbols", "Unicode" }

    startproject "mk1"

    configuration "Release"
        flags "OptimizeSize"

    configuration  { "Debug" }
        targetsuffix "-d"

    project "fmt"
        uuid "3CBD1488-3E74-4E30-A93D-2F33382702D8"

        includedirs "./ext/fmt/include"
        files { "./ext/fmt/src/format.cc", "./ext/fmt/src/os.cc" }
        vpaths { ["*"] = "ext/fmt/**" }

        kind "StaticLib"
        language "C++"

        location "build"
        targetdir "./build/lib/"
        objdir "./build/obj/fmt"

    project "lua"
        uuid "48cd469b-244c-468d-8a0a-c1ba5efceacd"

        includedirs "./ext/lua/src"
        files { "./ext/lua/src/**" }
        files { "./ext/lua/src/luac.c" }
        vpaths { ["*"] = "ext/lua/**" }

        kind "StaticLib"
        language "C"

        defines { "_CRT_SECURE_NO_WARNINGS" }
        location "build"
        targetdir "./build/lib/"
        objdir "./build/obj/lua"

    project "mk1"
        uuid "6271B6DA-BDD1-4105-90DD-90C438DC97F2"

        flags { "WinMain", "ExtraWarnings" }

        includedirs {
            "./src",
            "./ext/fmt/include",
            "./ext/lua/src",
            "./ext/sdl2/include",
            "./ext/utf8/",
        }
        files { "./src/**" }
        links { "fmt", "lua" }

        kind "WindowedApp"
        language "C++"

        location "build"
        debugdir  "./bin/"
        objdir    "./build/obj/mk1"


        configuration "x64"
            targetdir "./bin/x64"

        configuration  "x32"
            targetdir "./bin/x86"

        configuration "gmake"
            buildoptions(GCC_BUILD_OPTS)
            buildoptions(popen_result("sdl2-config --cflags"))
            buildoptions {
                "-isystem../ext/utf8/include",
            }

            linkoptions(popen_result("sdl2-config --static-libs"))
            linkoptions(popen_result("sdl2-config --libs"))

        configuration "vs*"
            buildoptions(MSVC_BUILD_OPTS)
            links { "SDL2", "SDL2main" }

        configuration  { "vs*", "x64" }
            libdirs "./ext/sdl2/lib/x64"
    
        configuration  { "vs*", "x32" }
            libdirs "./ext/sdl2/lib/x86"
