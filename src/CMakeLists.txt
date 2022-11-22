set(HEADER_FILES
        Earley.hpp
        )

set(SOURCE_FILES
        Earley.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})