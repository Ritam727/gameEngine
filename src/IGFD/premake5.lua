project "IGFD"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    libdirs {
        "../../lib"
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

    buildoptions {
        "-O2",
        "-funroll-loops"
    }