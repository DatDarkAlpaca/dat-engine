﻿cmake_minimum_required(VERSION 3.8)

set(TARGET_NAME "dat-engine")

file (GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (${TARGET_NAME} SHARED ${SOURCE_FILES})

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glew-cmake" "vendor/glew-cmake")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glfw" "vendor/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glm" "vendor/glm")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/spdlog" "vendor/spdlog")

target_include_directories(${TARGET_NAME} 
	PUBLIC
		${PROJECT_SOURCE_DIR}/vendor/stb
		${CMAKE_CURRENT_SOURCE_DIR}/src
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

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

target_compile_definitions(${TARGET_NAME} PRIVATE DAT_EXPORT)