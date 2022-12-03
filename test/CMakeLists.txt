add_subdirectory(lib/gtest-1.11.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runTests
        situation-test.cpp
        grammar-test.cpp
        earley-test.cpp
        main.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests src)