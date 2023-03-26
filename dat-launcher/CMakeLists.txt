cmake_minimum_required (VERSION 3.16)

set(TARGET_NAME "dat-launcher")

add_executable (${TARGET_NAME} "src/Main.cpp")

target_link_directories(${TARGET_NAME} PUBLIC dat-engine)

target_link_libraries (${TARGET_NAME} dat-engine)

target_compile_definitions (${TARGET_NAME} PRIVATE DAT_IMPORT)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/res)

add_custom_command(
        TARGET copy-resources POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_BINARY_DIR}/dat-launcher/res/
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/res
)

add_dependencies(${TARGET_NAME} copy-resources)
