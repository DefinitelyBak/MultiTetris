add_library(
    Common
  ##SHARED пока не разобрался как правильно работать с shared library
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Notification/AbstractNotificationHandler.cpp
)

target_include_directories(
    Common 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
