cmake_minimum_required(VERSION 3.16)
project(Formal_languages_2022)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS --coverage)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()


set(SOURCE_FILES main.cpp)
add_executable(formal_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(formal_run src)
