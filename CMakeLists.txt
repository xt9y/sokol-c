cmake_minimum_required(VERSION 4.2)
project(vorschau C OBJC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(vorschau main.c)
set_source_files_properties(main.c PROPERTIES LANGUAGE OBJC)

if(APPLE)
    target_link_libraries(vorschau
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework MetalKit"
    )
endif()
