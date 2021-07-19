# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
#project(project_name VERSION "0.0.0")
#configure_file(${path to configure file 'config.h.in'}
#include_directories(${PROJECT_BINARY_BIN})

# this allows the 'config.h' file to be used throughout the program

project(app)