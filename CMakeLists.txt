cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

project( egl_tests )

find_package( OpenGL REQUIRED COMPONENTS OpenGL EGL )

add_executable( main_egl
                main.cpp )
target_link_libraries( main_egl PRIVATE OpenGL::OpenGL OpenGL::EGL )

add_subdirectory( examples )