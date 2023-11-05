# Component

add_subdirectory(shape)

set (KE_SOURCES
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/animation_sprite.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/camera.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/component.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/texture_container.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/sprite.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/text.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/component/visual_component.h

    ${CMAKE_CURRENT_SOURCE_DIR}/animation_sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texture_container.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual_component.cpp
    ${KE_SOURCES}
    PARENT_SCOPE
)

