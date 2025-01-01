cmake_minimum_required(VERSION 3.14)
project(Controller
    VERSION 1.0.0
    DESCRIPTION "Tetris Game Controller Library"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# CONTROLLER_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(CONTROLLER_SHARED_LIBS "Build shared lib" OFF)
option(CONTROLLER_BUILD_DOCS "Build Controller documentation" OFF)
option(CONTROLLER_INSTALL "Generate target for installing Controller" ${is_top_level})
set_if_undefined(CONTROLLER_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Controller" CACHE STRING
    "Install path for Controller package-related CMake files")

if(DEFINED CONTROLLER_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CONTROLLER_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(Controller) # initialized below
add_library(Controller::Controller ALIAS Controller)

#----------------------------------------------------------------------------------------------------------------------
# Controller dependencies
#----------------------------------------------------------------------------------------------------------------------

find_package(Boost REQUIRED)

target_link_libraries(
    Controller
  PRIVATE
    Model
    Boost::boost
  )

#----------------------------------------------------------------------------------------------------------------------
# Controller sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(Controller EXPORT_FILE_NAME Include/Controller/${export_file_name})

set(sources
    Include/Controller/MoveController.h
    Include/Controller/Precompile.h
    Include/Controller/TimeController.h
    Include/Controller/Export.h
    Source/MoveController.cpp
    Source/Precompile.cpp
    Source/TimeController.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# Controller target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(Controller PRIVATE ${sources})
target_compile_definitions(Controller PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CONTROLLER_STATIC_DEFINE>")

target_include_directories(Controller
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>")

set_target_properties(Controller PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(CONTROLLER_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/Controller-config.cmake.in Controller-config.cmake
        INSTALL_DESTINATION "${CONTROLLER_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(Controller-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS Controller EXPORT Controller_export
        RUNTIME COMPONENT Controller
        LIBRARY COMPONENT Controller NAMELINK_COMPONENT Controller-dev
        ARCHIVE COMPONENT Controller-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY Include/
        TYPE INCLUDE
        COMPONENT Controller-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Include/Controller/${export_file_name}"
        COMPONENT Controller-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Controller")

    set(targets_file "Controller-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "Controller-static-targets.cmake")
    endif()

    install(EXPORT Controller_export
        COMPONENT Controller-dev
        FILE "${targets_file}"
        DESTINATION "${CONTROLLER_INSTALL_CMAKEDIR}"
        NAMESPACE Controller::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/Controller-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/Controller-config-version.cmake"
        COMPONENT Controller-dev
        DESTINATION "${CONTROLLER_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:Controller>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:Controller>/$<TARGET_FILE_PREFIX:Controller>$<TARGET_FILE_BASE_NAME:Controller>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT Controller-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(CONTROLLER_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()