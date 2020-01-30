cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

project( egl_tests )

find_package( OpenGL REQUIRED COMPONENTS OpenGL EGL )

include_directories( "ext/glad/" )
set( GLAD_SRCS
     "ext/glad/egl.c"
     "ext/glad/gl.c" )

add_executable( main_egl
                main_egl.cpp )
target_link_libraries( main_egl PRIVATE OpenGL::OpenGL OpenGL::EGL )

add_executable( main
                main.cpp
                ${GLAD_SRCS} )
target_link_libraries( main PRIVATE OpenGL::OpenGL OpenGL::EGL dl )

add_subdirectory( examples )