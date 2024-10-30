function create_project(project_name, project_kind)
    project(project_name)
        kind(project_kind)
        language "C++"
        cppdialect "C++17"

        targetdir(binaries_path .. "/%{prj.name}")
        objdir(intermediate_path .. "/%{prj.name}")

        pchheader "pch.hpp"
        pchsource "src/pch.cpp"

        files {
            "src/**.cpp",
            "src/**.hpp",
            "src/**.c",
            "src/**.h",
        }
    
        includedirs {
            "%{prj.location}",
            "%{prj.location}/src"
        }

        -- Configurations
        filter { "configurations:Debug" }
            runtime "Debug"
            symbols "on"
        filter { }
            
        filter { "configurations:Release" }
            runtime "Release"
            optimize "on"
            inlining "auto"
        filter { }

		-- Platform 
		detect_platform()
		
		-- Vendor
		setup_vendors()
end