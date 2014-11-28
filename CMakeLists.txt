cmake_minimum_required(VERSION 2.8)
project(SOCS)

find_package(PkgConfig)
find_package(Boost REQUIRED COMPONENTS system thread python3)
find_package(OpenGL)
find_package(PythonLibs)

pkg_search_module(GTKMM gtkmm-3.0)
pkg_search_module(GLFW REQUIRED glfw3)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

#add_executable(test test.cpp)
add_library(test SHARED test.cpp)

target_link_libraries(test ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${GTKMM_LIBRARIES} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
