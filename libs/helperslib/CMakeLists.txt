cmake_minimum_required(VERSION 3.6)

project(helperslib  LANGUAGES CXX)

add_library(${PROJECT_NAME}
INTERFACE
    include/streamredirect.hpp
)

target_include_directories(${PROJECT_NAME}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
