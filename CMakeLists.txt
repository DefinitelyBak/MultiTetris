cmake_minimum_required(VERSION 3.15)
project(DDD VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
