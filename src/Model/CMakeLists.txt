add_library(
    Model
  ##SHARED пока не разобрался как правильно работать с shared library
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Precompile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/ModelGame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Blocks/AbstractBlock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Map.cpp
)

target_include_directories(
    Model 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)