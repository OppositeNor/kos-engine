add_subdirectory(unit_test_math)
add_subdirectory(unit_test_shape)

set(KE_TEST_SOURCES
        ${KE_TEST_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test.cpp
        PARENT_SCOPE)