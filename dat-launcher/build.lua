create_project("dat-launcher", "ConsoleApp")
links { "dat-engine" }
includedirs {
    "%{wks.location}/dat-engine/src",
}