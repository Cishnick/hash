

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(BINARY ${CMAKE_PROJECT_NAME}_tst)

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc)

file(GLOB TEST_SOURCES
     "*.h"
     "*.cc"
)

add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)

add_test(${BINARY} ${BINARY})

gtest_discover_tests(${BINARY})

message(STATUS "----------VARIABLE--------------")
message(STATUS "${TEST_SOURCES}")
message(STATUS "${BINARY}")