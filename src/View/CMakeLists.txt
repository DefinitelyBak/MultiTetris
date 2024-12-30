cmake_minimum_required(VERSION 3.14)
project(View
    VERSION 1.0.0
    DESCRIPTION "Tetris Game View Library"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# VIEW_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(VIEW_SHARED_LIBS "Build shared lib" OFF)
option(VIEW_BUILD_DOCS "Build View documentation" OFF)
option(VIEW_INSTALL "Generate target for installing View" ${is_top_level})
set_if_undefined(VIEW_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/View" CACHE STRING
    "Install path for View package-related CMake files")

if(DEFINED VIEW_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${VIEW_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(View) # initialized below
add_library(View::View ALIAS View)

#----------------------------------------------------------------------------------------------------------------------
# View dependencies
#----------------------------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

find_package(SFML)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

find_package(Boost REQUIRED)

target_link_libraries(
    View
  PUBLIC
    Model
    Controller
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
  PUBLIC
    SFML::System
    SFML::Graphics
    SFML::Window
    SFML::Main
  )

#----------------------------------------------------------------------------------------------------------------------
# View sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(View EXPORT_FILE_NAME Include/View/${export_file_name})

set(sources
#Qt headers
    Include/View/Qt/KeyPressFilter.h
    Include/View/Qt/Map.h
    Include/View/Qt/PreviewBlock.h
    Include/View/Qt/QAdapterWidget.h
    Include/View/Qt/QtApplication.h
    Include/View/Qt/Widget.h
#SFML headers
    Include/View/SFML/Map.h
    Include/View/SFML/SFMLApplication.h
    Include/View/SFML/Text.h
    Include/View/SFML/Widget.h
    Include/View/SFML/WidgetPreviewBlock.h

    Include/View/Forwards.h
    Include/View/IApplication.h
    Include/View/Precompile.h
    Include/View/Export.h
#Qt cpp files
    Source/Qt/Map.cpp
    Source/Qt/PreviewBlock.cpp
    Source/Qt/QtApplicaion.cpp
    Source/Qt/Widget.cpp
#SFML cpp files
    Source/SFML/Map.cpp
    Source/SFML/SFMLApplication.cpp
    Source/SFML/Text.cpp
    Source/SFML/Widget.cpp
    Source/SFML/WidgetPreviewBlock.cpp
# Common cpp files
    Source/Precompile.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# View target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(View PRIVATE ${sources})
target_compile_definitions(View PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:VIEW_STATIC_DEFINE>")

target_include_directories(View
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>")

set_target_properties(View PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(VIEW_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/View-config.cmake.in View-config.cmake
        INSTALL_DESTINATION "${VIEW_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(View-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS View EXPORT View_export
        RUNTIME COMPONENT View
        LIBRARY COMPONENT View NAMELINK_COMPONENT View-dev
        ARCHIVE COMPONENT View-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY Include/
        TYPE INCLUDE
        COMPONENT View-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Include/View/${export_file_name}"
        COMPONENT View-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/View")

    set(targets_file "View-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "View-static-targets.cmake")
    endif()

    install(EXPORT View_export
        COMPONENT View-dev
        FILE "${targets_file}"
        DESTINATION "${VIEW_INSTALL_CMAKEDIR}"
        NAMESPACE View::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/View-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/View-config-version.cmake"
        COMPONENT View-dev
        DESTINATION "${VIEW_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:View>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:View>/$<TARGET_FILE_PREFIX:View>$<TARGET_FILE_BASE_NAME:View>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT View-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(VIEW_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()