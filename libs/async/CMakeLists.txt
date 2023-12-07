cmake_minimum_required(VERSION 3.6)

project(async LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
    include/async.h
    src/async.cpp
    # src/asyncbulkprinter.hpp
)

# set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    bulklib
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include  
)
