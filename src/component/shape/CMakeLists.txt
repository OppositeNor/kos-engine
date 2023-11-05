# Shape

set (KE_SOURCES
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/shape/shape_circle.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/shape/shape_rect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shape_circle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shape_rect.cpp
    ${KE_SOURCES}
    PARENT_SCOPE
)