cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(myapp VERSION 1.0)

add_definitions(-std=c++17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

add_executable(myapp main.cpp)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(myapp PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(myapp "-framework Cocoa")
target_link_libraries(myapp "-framework OpenGL")
target_link_libraries(myapp "-framework IOKit")
target_link_libraries(myapp glfw ${OPENGL_gl_LIBRARY})
