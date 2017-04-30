cmake_minimum_required(VERSION 2.8.11)

project(ui_prediction)

find_package(OpenCV 3 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
FIND_PACKAGE(Boost 1.54 COMPONENTS python REQUIRED)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB CPP_FILES ${CMAKE_SOURCE_DIR}/source/*.cpp)

find_package(Qt5Widgets)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/source)

link_directories(${PYTHON_LIBRARIES})


# Tell CMake to create the helloworld executable
add_executable(${PROJECT_NAME} ${CPP_FILES})

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${OpenCV_LIBS} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
