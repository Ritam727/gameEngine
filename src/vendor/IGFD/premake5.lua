project "IGFD"
    kind "SharedLib"
    language "C++"

    targetdir "../../../lib"
    objdir "../../../objects"

    libdirs {
        "../../../lib"
    }

    includedirs {
        "../"
    }

    files {
        "*.cpp"
    }

    links {
        "imgui"
    }

    filter "configurations:Release"
        defines {
            "LOGGER_WARN",
            "ENVIRONMENT_DEBUG"
        }

        buildoptions {
            "-O2"
        }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }

        defines {
            "LOGGER_DEBUG",
            "ENVIRONMENT_DEBUG"
        }

        symbols "On"