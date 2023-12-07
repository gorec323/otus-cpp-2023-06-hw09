cmake_minimum_required(VERSION 3.6)

project(bulklib  LANGUAGES CXX)

add_library(${PROJECT_NAME}
    include/bulk.hpp
    src/bulk.cpp
    include/commandscontroller.hpp
    src/commandscontroller.cpp
    include/bulkprinter.hpp
    src/bulkprinter.cpp
    include/consolebulkprinter.hpp
    include/filebulkprinter.hpp
    src/asyncbulkprinter.hpp
)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    printlib
)
