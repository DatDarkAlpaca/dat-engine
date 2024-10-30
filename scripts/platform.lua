function detect_platform()
    filter { "system:Windows" }
        defines {
            "DAT_PLATFORM_WINDOWS"
        }
        files {
            -- Windows files
        }
        links {
            -- Windows libraries
        }
    filter { }

    filter { "system:Unix or linux" }
		defines {
            "DAT_PLATFORM_LINUX"
        }
    filter { }

    filter { "system:macosx" }
		defines {
            "DAT_PLATFORM_MACOSX"
        }
    filter { }
end
