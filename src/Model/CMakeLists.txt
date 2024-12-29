cmake_minimum_required(VERSION 3.14)
project(Model
    VERSION 1.0.0
    DESCRIPTION "Tetris Game Model Library"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# MODEL_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(MODEL_SHARED_LIBS "Build shared lib" OFF)
option(MODEL_BUILD_TESTS "Build Model tests" OFF)
option(MODEL_BUILD_DOCS "Build Model documentation" OFF)
option(MODEL_INSTALL "Generate target for installing Model" ${is_top_level})
set_if_undefined(MODEL_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Model" CACHE STRING
    "Install path for Model package-related CMake files")

if(DEFINED MODEL_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${MODEL_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(Model) # initialized below
add_library(Model::Model ALIAS Model)

#----------------------------------------------------------------------------------------------------------------------
# Model dependencies
#----------------------------------------------------------------------------------------------------------------------

find_package(Boost REQUIRED)

#----------------------------------------------------------------------------------------------------------------------
# Model sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(Model EXPORT_FILE_NAME Include/Model/${export_file_name})

set(sources
    include/Model/AbstractModel.h
    include/Model/AbstractWidget.h
    include/Model/DescriptionModel.h
    include/Model/Export.h
    include/Model/ModelGame.h
    include/Model/Types.h
    Include/Model/Blocks/AbstractBlock.h
    Include/Model/Blocks/Iblock.h
    Include/Model/Blocks/Jblock.h
    Include/Model/Blocks/Lblock.h
    Include/Model/Blocks/Oblock.h
    Include/Model/Blocks/Sblock.h
    Include/Model/Blocks/Tblock.h
    Include/Model/Blocks/Zblock.h
    Include/Model/Factory/AbstractCreator.h
    Include/Model/Factory/BlocksFactory.h
    Include/Model/Factory/ObjectFactory.h
    Include/Model/Forwards.h
    Include/Model/Map.h
    Include/Model/Precompile.h
    Source/Blocks/AbstractBlock.cpp
    Source/Map.cpp
    Source/ModelGame.cpp
    Source/Precompile.cpp
    Source/Types.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# Model target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(Model PRIVATE ${sources})
target_compile_definitions(Model PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:MODEL_STATIC_DEFINE>")

target_include_directories(Model
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>"
        SYSTEM ${Boost_INCLUDE_DIRS})

set_target_properties(Model PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(MODEL_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/Model-config.cmake.in Model-config.cmake
        INSTALL_DESTINATION "${MODEL_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(Model-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS Model EXPORT Model_export
        RUNTIME COMPONENT Model
        LIBRARY COMPONENT Model NAMELINK_COMPONENT Model-dev
        ARCHIVE COMPONENT Model-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY Include/
        TYPE INCLUDE
        COMPONENT Model-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Include/Model/${export_file_name}"
        COMPONENT Model-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Model")

    set(targets_file "Model-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "Model-static-targets.cmake")
    endif()

    install(EXPORT Model_export
        COMPONENT Model-dev
        FILE "${targets_file}"
        DESTINATION "${MODEL_INSTALL_CMAKEDIR}"
        NAMESPACE Model::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/Model-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/Model-config-version.cmake"
        COMPONENT Model-dev
        DESTINATION "${MODEL_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:Model>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:Model>/$<TARGET_FILE_PREFIX:Model>$<TARGET_FILE_BASE_NAME:Model>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT Model-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(MODEL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MODEL_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()