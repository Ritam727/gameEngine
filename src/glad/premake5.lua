project "glad"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "include"
    }

    files {
        "src/glad.c"
    }
