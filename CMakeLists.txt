cmake_minimum_required(VERSION 3.18)
project(ModelLibrary)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(pybind11_DIR /home/shattang/.local/lib/python3.10/site-packages/pybind11/share/cmake/pybind11)

find_package(pybind11 REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})

add_library(model SHARED model.cpp bindings.cpp)

set_target_properties(model PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(model PRIVATE pybind11::module ${PYTHON_LIBRARIES})
