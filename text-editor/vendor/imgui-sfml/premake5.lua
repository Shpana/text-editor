project "imgui-sfml"
    kind "StaticLib"
    language "C++"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

    files {
        "**.h",
        "**.cpp",
    }

    includedirs {
        for_include["imgui"],
        for_include["sfml"],
    }

    links {
        "opengl32",
        "freetype",
    }

    libdirs {
        libs["sfml"],
    }

    defines {
        "SFML_STATIC",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    filter {"system:windows", "configurations:Debug"}
		runtime "Debug"
		symbols "on"

        links {
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib",
        }

	filter {"system:windows", "configurations:Release"}
		runtime "Release"
		optimize "on"

        links {
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib",
        }
