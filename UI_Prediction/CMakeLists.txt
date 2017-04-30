cmake_minimum_required(VERSION 2.8.11)

project(ui_prediction)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(${PROJECT_NAME} main.cpp ui_main_window.cpp ui_resultimage_area.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
