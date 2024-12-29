cmake_minimum_required(VERSION 3.14)
project(Model-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include("../cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    enable_testing()
endif()

#----------------------------------------------------------------------------------------------------------------------
# testing framework
#----------------------------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # do not override parent project's runtime settings on Windows
set(INSTALL_GTEST OFF)

# For simplicity, always build googletest as static library. This prevents mylib-tests executable from
# complaining about missing googletest DLLs on Windows.
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(googletest)

#----------------------------------------------------------------------------------------------------------------------
# tests dependencies
#----------------------------------------------------------------------------------------------------------------------

if(is_top_level)
    find_package(Model REQUIRED)
endif()

#----------------------------------------------------------------------------------------------------------------------
# tests sources
#----------------------------------------------------------------------------------------------------------------------

set(sources
    Source/BlockTest.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(Model-tests)
target_sources(Model-tests PRIVATE ${sources})

target_link_libraries(Model-tests
    PRIVATE
        Model::Model
        gtest_main)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(Model-tests Model::Model)
endif()

include(GoogleTest)
gtest_discover_tests(Model-tests)