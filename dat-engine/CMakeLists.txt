cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME "dat-engine")

# Sources:
file (GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file (GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# DLL:
add_library (${TARGET_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

# Vendor Includes:
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glew-cmake" "vendor/glew-cmake")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glfw" "vendor/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glm" "vendor/glm")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/spdlog" "vendor/spdlog")

target_include_directories(${TARGET_NAME} 
	PUBLIC
		${PROJECT_SOURCE_DIR}/vendor/stb
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/src/Core
		glm
		glfw
		libglew_static
		spdlog
)

target_link_libraries(${TARGET_NAME}
	PUBLIC
		glm
		glfw	
		libglew_static
		spdlog
)

# Platform Detection:
if (WIN32)
    target_compile_definitions (${TARGET_NAME} PRIVATE DAT_WINDOWS_PLATFORM)
endif()

if (APPLE)
    target_compile_definitions (${TARGET_NAME} PRIVATE DAT_MAC_PLATFORM)
endif()

if (UNIX AND NOT APPLE)
    target_compile_definitions (${TARGET_NAME} PRIVATE DAT_LINUX_PLATFORM)
endif()

target_precompile_headers(${TARGET_NAME} PUBLIC "src/pch.h")

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

target_compile_definitions(${TARGET_NAME} PRIVATE DAT_EXPORT)

add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/lib/dat-engine.dll
                ${CMAKE_BINARY_DIR}/dat-launcher/
        DEPENDS ${CMAKE_BINARY_DIR}/lib/dat-engine.dll)