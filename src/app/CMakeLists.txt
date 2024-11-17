add_executable(main main.cpp Source/SFMLApplication.cpp)
target_link_libraries(
    main
    PUBLIC
    Model
 PRIVATE
  sfml-graphics)
#target_compile_features(main PRIVATE cxx_std_14)


target_include_directories(
    main 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
  )

  set_property(TARGET main PROPERTY CXX_STANDARD 14)