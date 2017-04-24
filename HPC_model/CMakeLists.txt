cmake_minimum_required(VERSION 2.8)
project(cxxdemo1)
find_package(OpenCV 3 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
FIND_PACKAGE(Boost 1.54 COMPONENTS python REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB CPP_FILES ${CMAKE_SOURCE_DIR}/source/*)


include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
link_directories(${PYTHON_LIBRARIES})


add_executable(predict ${CPP_FILES})

target_link_libraries(predict ${OpenCV_LIBS} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
