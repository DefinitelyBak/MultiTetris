cmake_minimum_required(VERSION 3.20)
project(MultiTetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Model)
add_subdirectory(src/View)
add_subdirectory(src/Controller)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(SFML)
find_package(Qt5)

set(sources src/main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

set(Boost_USE_STATIC_LIBS ON)

add_executable(MultiTetris ${sources})
target_link_libraries(MultiTetris PRIVATE 
    Model::Model 
    View::View 
    Controller::Controller
    Boost::boost
    Boost::program_options
)

add_custom_command(
    TARGET MultiTetris
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/View/Resources"
        "$<TARGET_FILE_DIR:MultiTetris>/Resources"
    COMMENT "Copying Resources to target directory"
    VERBATIM
)
