set(HEADER_FILES
        Earley.hpp
        Situation.hpp
        Grammar.hpp
        )

set(SOURCE_FILES
        Earley.cpp
        Situation.cpp
        Grammar.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})