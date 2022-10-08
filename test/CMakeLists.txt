add_executable(runTests
        ksuffix-test.cpp
        main.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests src)