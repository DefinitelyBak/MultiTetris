add_library(
    View
  ##SHARED пока не разобрался как правильно работать с shared library
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFMLWidget.cpp
)

target_include_directories(
  View 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
  )

target_link_libraries(
    View
  PUBLIC
    Model
    Controllers
  PRIVATE
    sfml-graphics)