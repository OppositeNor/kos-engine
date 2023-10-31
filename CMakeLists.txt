cmake_minimum_required(VERSION 3.15)

project(KosEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list(APPEND CG_RESOURCES image_resource.cgures)
list(APPEND CG_RESOURCES text_resource.cgures)
list(APPEND CG_RESOURCES font_resource.cgures)

add_subdirectory(./dependencies/cos-graphics)
add_subdirectory(${CGRW_PATH})


if (USE_UTF16LE MATCHES ON)
    add_definitions(-DCG_USE_UTF16LE)
endif()

include_directories(${PROJECT_SOURCE_DIR}/dependencies/cos-graphics/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src/component)
add_subdirectory(src/game)
add_subdirectory(src/interface)
add_subdirectory(src/math)
add_subdirectory(src/input_handler)
add_subdirectory(src/test)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/lib/${CMAKE_SYSTEM_NAME})
file (MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_library(${PROJECT_NAME} 
    ${KE_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${CG_LIB_OUTPUT_NAME}
)
