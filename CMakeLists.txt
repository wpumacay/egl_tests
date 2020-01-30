cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

project( egl_tests )

find_package( OpenGL REQUIRED COMPONENTS OpenGL EGL )
find_package( GLEW REQUIRED )

add_executable( main_egl
                main_egl.cpp )
target_link_libraries( main_egl PRIVATE OpenGL::OpenGL OpenGL::EGL )

add_executable( main
                main.cpp )
target_link_libraries( main PRIVATE OpenGL::OpenGL OpenGL::EGL ${GLEW_LIBRARIES} )

add_subdirectory( examples )