set(HEADER_FILES
        ksuffix.hpp
        )

set(SOURCE_FILES
        ksuffix.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})