cmake_minimum_required(VERSION 3.14)
project(MultiTetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Model)
add_subdirectory(src/View)
add_subdirectory(src/Controller)

set(BOOST_INCLUDE_LIBRARIES math filesystem system program_options thread)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0.7z
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

set(sources src/main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(MultiTetris)
target_sources(MultiTetris PRIVATE ${sources})
target_link_libraries(MultiTetris PUBLIC 
    Model::Model 
    View::View 
    Controller::Controller
    Boost::math 
    Boost::filesystem
    Boost::program_options
    Boost::thread
)
set_target_properties(MultiTetris PROPERTIES LINK_FLAGS "-Wl,-Bstatic")

if(NOT is_top_level)
    win_copy_deps_to_target_dir(MultiTetris Model::Model View::View Controller::Controller)
endif()

add_custom_command(
    TARGET MultiTetris
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/View/Resources"
        "$<TARGET_FILE_DIR:MultiTetris>/Resources"
    COMMENT "Copying Resources to target directory"
    VERBATIM
)
