cmake_minimum_required(VERSION 3.16)
project(Formal_languages_2022)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(Formal_languages_2022
        src/ksuffix.cpp
        src/ksuffix.hpp
        main.cpp)
