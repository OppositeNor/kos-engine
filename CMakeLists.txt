cmake_minimum_required(VERSION 3.15)

project(KosEngine)

add_subdirectory(./dependencies/cos-graphics)
add_subdirectory(${CGRW_PATH})

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/lib/${CMAKE_SYSTEM_NAME})
file (MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/exe/${CMAKE_SYSTEM_NAME})
file (MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})


if (USE_UTF16LE MATCHES ON)
    add_definitions(-DCG_USE_UTF16LE)
endif()

include_directories(${PROJECT_SOURCE_DIR}/dependencies/cos-graphics/include)

add_executable(${PROJECT_NAME} 
    ./src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${CG_LIB_OUTPUT_NAME}
)
