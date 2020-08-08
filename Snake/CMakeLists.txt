cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 17)

# source files
set(SOURCE_FILES src/main.cpp
    src/States/Core.cpp
    include/States/Core.hpp
    include/States/State.hpp
    src/States/GameState.cpp
    include/States/GameState.hpp
    src/Entities/Snake.cpp
    include/Entities/Snake.hpp
    src/Clock/Clock.cpp
    include/Clock/Clock.hpp
    src/Entities/Food.cpp
    include/Entities/Food.hpp
    include/Random/Random.hpp
    src/Random/Random.cpp
    include/GUI/GUI.hpp
    src/GUI/GUI.cpp
    include/GUI/Button.hpp
    src/GUI/Button.cpp
    include/GUI/ScoreBar.hpp
    include/GUI/StatusBar.hpp
    src/GUI/ScoreBar.cpp
    src/GUI/StatusBar.cpp
    src/States/MainMenuState.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5.1 COMPONENTS network window graphics system REQUIRED)

# include directories
include_directories(
    "${PROJECT_SOURCE_DIR}/include/States"
    "${PROJECT_SOURCE_DIR}/include/Entities"
    "${PROJECT_SOURCE_DIR}/include/Clock"
    "${PROJECT_SOURCE_DIR}/include/Random"
    "${PROJECT_SOURCE_DIR}/include/GUI"
    ${SFML_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})