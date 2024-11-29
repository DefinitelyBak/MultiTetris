add_executable(main main.cpp)

#target_compile_features(main PRIVATE cxx_std_14)


target_include_directories(
    main 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
  )

  target_link_libraries(
    main
  PUBLIC
    View
    Controllers
    Model
  PRIVATE
    sfml-graphics
    )


if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()