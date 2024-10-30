require "scripts/clear"
require "scripts/project"
require "scripts/platform"
require "vendor/dependencies"

workspace "dat-engine"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    startproject "dat-launcher"

    flags {
		"MultiProcessorCompile"
	}

output_path         = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
binaries_path       = "%{wks.location}/build/bin/" .. "%{output_path}"
intermediate_path   = "%{wks.location}/build/intermediate/" .. "%{output_path}"
vendor_path         = "%{wks.location}/vendor/"


group "dependencies"
	include "vendor/glfw.lua"
    include "vendor/glad.lua"
    include "vendor/imgui.lua"
    include "vendor/vma.lua"
	include "vendor/imgui-glfw.lua"
    include "vendor/imgui-opengl.lua"
	include "vendor/imgui-vulkan.lua"
group ""

include "dat-engine/build.lua"
include "dat-launcher/build.lua"
