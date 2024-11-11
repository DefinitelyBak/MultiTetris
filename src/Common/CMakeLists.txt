add_library(
    Common
  ##SHARED пока не разобрался как правильно работать с shared library
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/AbstractObservable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/AbstractObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Commands/AbstractCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Commands/UpdateMapCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Precompile.cpp
)

target_include_directories(
    Common 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
