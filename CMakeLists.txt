cmake_minimum_required(VERSION 4.2)
project(vorschau C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(vorschau main.c)

if(APPLE)
    set_source_files_properties(main.c PROPERTIES LANGUAGE OBJC)
    target_link_libraries(vorschau PRIVATE
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework MetalKit"
    )
elseif(WIN32)
    target_link_libraries(vorschau PRIVATE
        kernel32 user32 shell32 gdi32 d3d11 dxgi
    )
elseif(UNIX)
    target_link_libraries(vorschau PRIVATE
        X11 Xi Xcursor GL dl pthread m
    )
    target_compile_options(vorschau PRIVATE -pthread)
    target_link_options(vorschau PRIVATE -pthread)
endif()
