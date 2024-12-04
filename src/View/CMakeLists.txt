add_library(
    View
  ##SHARED пока не разобрался как правильно работать с shared library
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFMLWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFMLMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SFMLPreviewBlock.cpp
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

if(WIN32)
  add_custom_command(
    TARGET View
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
    VERBATIM)
endif()