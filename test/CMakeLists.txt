add_subdirectory(lib/googletest)

include_directories(${gtest_SOURCE_FIR}/include ${gtest_SOURCE_FIR})

add_executable(runTests
        ksuffix-test.cpp
        main.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests src)