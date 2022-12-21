set(BINARY ${CMAKE_PROJECT_NAME})

set(MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

file(GLOB SOURCES
     "*.h"
     "*.cpp"
)

set(SOURCES_LIB ${SOURCES})
list(REMOVE_ITEM SOURCES_LIB ${MAIN_FILE})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
