include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  Tests
  ## Model
  #${CMAKE_CURRENT_SOURCE_DIR}/Source/Precompile.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/BlockTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../model/Source/Precompile.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../model/Source/ModelGame.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../model/Source/Blocks/AbstractBlock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../model/Source/Types.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../model/Source/Map.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/MapTest.cpp

)

target_include_directories(
    Tests 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../model/Include
)

target_link_libraries(
    Tests
  PRIVATE
    #Model
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests PROPERTIES TIMEOUT 600)
