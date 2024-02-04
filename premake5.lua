workspace "text-editor"
    architecture "x64"
    startproject "text-editor"

    configurations {
        "Debug", 
        "Release",
    }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

for_include = {}
for_include["imgui"] = "%{wks.location}/text-editor/vendor/imgui"
for_include["imgui-sfml"] = "%{wks.location}/text-editor/vendor/imgui-sfml"
for_include["sfml"] = "%{wks.location}/text-editor/vendor/sfml/include"

libs = {}
libs["sfml"] = "%{wks.location}/text-editor/vendor/sfml/lib"

group "dependencies"
    include "text-editor/vendor/imgui"
    include "text-editor/vendor/imgui-sfml"
group ""

group "app"
    include "text-editor"
group ""
