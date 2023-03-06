cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME "dat-launcher")

add_executable (${TARGET_NAME} "src/Main.cpp")

target_link_directories(${TARGET_NAME} PUBLIC dat-engine)

target_link_libraries (${TARGET_NAME} dat-engine)

if (WIN32)
    target_compile_definitions (${TARGET_NAME} PRIVATE DAT_WINDOWS_PLATFORM)
endif()

if (APPLE)
    target_compile_definitions (${TARGET_NAME} PRIVATE DAT_MAC_PLATFORM)
endif()

if (UNIX AND NOT APPLE)
    target_compile_definitions (${TARGET_NAME} PRIVATE DAT_LINUX_PLATFORM)
endif()

target_compile_definitions (${TARGET_NAME} PRIVATE DAT_IMPORT)

# Post Build:
add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_BINARY_DIR}/dat-launcher/res/)