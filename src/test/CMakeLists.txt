cmake_minimum_required(VERSION 3.15)
project(KosEngineTest)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/exe/${CMAKE_SYSTEM_NAME})
file (MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_executable( ${PROJECT_NAME}
    ${KE_SOURCES}
    ${PROJECT_SOURCE_DIR}/test_main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CG_LIB_OUTPUT_NAME}
)