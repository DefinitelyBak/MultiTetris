add_library(
    Controllers
  ##SHARED пока не разобрался как правильно работать с shared library
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/MoveController.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/TimeController.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/Precompile.cpp
)

target_include_directories(
    Controllers 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(
    Controllers
  PUBLIC
    Model
)

