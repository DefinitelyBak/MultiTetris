include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(
    Model
  ##SHARED пока не разобрался как правильно работать с shared library
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Batch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OrderLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OrderLineHash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exception/OutOfStock.cpp
)

target_include_directories(
    Model 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../External)