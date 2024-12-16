#include_directories(${Qt5Widgets_INCLUDE_DIRS})



add_library(
    View
  ##SHARED пока не разобрался как правильно работать с shared library
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFML/Widget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFML/Map.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFML/WidgetPreviewBlock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFML/SFMLApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFML/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Precompile.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Qt/Adapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Qt/QtApplicaion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Qt/Widget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Qt/Map.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Qt/QAdapterWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Qt/PreviewBlock.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/QtApplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/QAdapterWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/KeyPressFilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/Widget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/Map.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/Adapter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Qt/PreviewBlock.h
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
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
  PRIVATE
    sfml-graphics
  )

target_compile_definitions(View PRIVATE VIEW_LIBRARY)

if(WIN32)
  add_custom_command(
    TARGET View
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:View>
    VERBATIM)
endif()