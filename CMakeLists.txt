cmake_minimum_required(VERSION 3.28)
project(Tetris VERSION 1.0.0 LANGUAGES CXX)

enable_testing()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(Qt5_DIR "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5") 



find_package(QT NAMES Qt5 COMPONENTS Gui Widgets Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets Core)

if(Qt5_FOUND)
    message(STATUS "Qt5 found: ${Qt5_DIR}")
else()
    message(FATAL_ERROR "Qt5 not found!")
endif()


find_package(Boost REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/controllers)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/view)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(Tetris ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(
    Tetris
  PUBLIC
    View
    Controllers
    Model
  PRIVATE
    sfml-graphics
    )

if(WIN32)
    add_custom_command(
        TARGET Tetris
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Tetris>
        VERBATIM)
endif()
