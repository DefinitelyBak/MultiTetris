cmake_minimum_required(VERSION 3.28)
project(Tetris VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/controllers)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/view)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
