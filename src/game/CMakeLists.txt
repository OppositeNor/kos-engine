# Game
set(KE_SOURCES

    ${PROJECT_SOURCE_DIR}/include/kos_engine/game.h
    ${PROJECT_SOURCE_DIR}/include/kos_engine/game_factory.h

    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game_factory.cpp
    ${KE_SOURCES}
    PARENT_SCOPE
)