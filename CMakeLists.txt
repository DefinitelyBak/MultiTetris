cmake_minimum_required(VERSION 3.14)
project(MultiTetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Model)

set(sources src/main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(MultiTetris)
target_sources(MultiTetris PRIVATE ${sources})
target_link_libraries(MultiTetris PRIVATE Model)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(MultiTetris Model)
endif()
