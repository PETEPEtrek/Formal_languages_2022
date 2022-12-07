cmake_minimum_required(VERSION 3.16)
project(Formal_languages_2022)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS --coverage)

set(SOURCE_FILES main.cpp)
add_executable(formal_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(formal_run src)