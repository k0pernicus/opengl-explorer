cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(opengl-explorer VERSION 1.0)

add_definitions(-std=c++17)
set(CXX_FLAGS "-Wall" "-Werror" "-Wextra" "-fsanitize=undefined,address")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

add_executable(opengl-explorer maths_utils.cpp shader_utils.cpp main.cpp)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(opengl-explorer PUBLIC ${OPENGL_INCLUDE_DIR})

if (APPLE)
    target_link_libraries(opengl-explorer "-framework Cocoa")
    target_link_libraries(opengl-explorer "-framework OpenGL")
    target_link_libraries(opengl-explorer "-framework IOKit")
endif (APPLE)
target_link_libraries(opengl-explorer glfw ${OPENGL_gl_LIBRARY})
