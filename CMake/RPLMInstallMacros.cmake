FUNCTION(_PRIVATE_RPLM_INSTALL TARGET_NAME INSTALL_BIN_PATH INSTALL_LIB_PATH INSTALL_INCLUDE_PATH INSTALL_PDB_PATH
    #COMPONENTS
    )
    IF (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Include")
        SET(INCLUDE_PATH_EXISTS 1)
    ENDIF()
    
    IF (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Resources" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
        SET(RESOURCES_PATH_EXISTS 1)
    ENDIF()
    
    #message(STATUS "install bin:${INSTALL_BIN_PATH}")
    #message(STATUS "path:${CMAKE_INSTALL_PREFIX}/${INSTALL_BIN_PATH}")
    FOREACH(CONFIG ${CMAKE_INSTALL_CONFIG_NAME})
        #Copy targets
        INSTALL(TARGETS ${TARGET_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${INSTALL_BIN_PATH} 
                #COMPONENT ${COMPONENT} 
            CONFIGURATIONS ${CONFIG}
            LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${INSTALL_BIN_PATH} 
                #COMPONENT ${COMPONENT} 
            CONFIGURATIONS ${CONFIG}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_PATH}
                #COMPONENT ${COMPONENT} 
            CONFIGURATIONS ${CONFIG}
            )
        if (MSVC AND RPLM_BUILD_PDB)
            if ($ENV{RPLM_INSTALL_PDB} AND $ENV{RPLM_INSTALL_PDB} EQUAL 1)
                install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}> DESTINATION ${CMAKE_INSTALL_PREFIX}/${INSTALL_PDB_PATH} OPTIONAL)
            endif()
        endif()
    ENDFOREACH()

    IF (INCLUDE_PATH_EXISTS 
        #AND ${COMPONENT} STREQUAL "SDK"
        )
        INSTALL(DIRECTORY Include/ 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${INSTALL_INCLUDE_PATH} 
            #COMPONENT ${COMPONENT}
            )
    ENDIF()
    #Copy resources folder 
    IF (RESOURCES_PATH_EXISTS)
        #message(${TARGET_NAME} Resources ${INSTALL_BIN_PATH}/${CONFIG})
            
        INSTALL(DIRECTORY Resources/ 
            DESTINATION ${INSTALL_BIN_PATH}/Resources
            #COMPONENT ${COMPONENT} 
            COMPONENT   copy-files
            PATTERN *.rc* EXCLUDE
            )
    ENDIF()
    #ENDFOREACH()
ENDFUNCTION()

#------------------------------------------------------------------------------

FUNCTION(RPLM_INSTALL_APPLICATION) 
    SET(ONE_VALUE_ARGS TARGET)
    SET(MULTI_VALUE_ARGS FILES)

    CMAKE_PARSE_ARGUMENTS(PARAM "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})
    
    IF (PARAM_TARGET)
        _PRIVATE_RPLM_INSTALL(${PARAM_TARGET} ${APP_INSTALL_BIN} ${APP_INSTALL_LIB} ${APP_INSTALL_INCLUDE} ${APP_INSTALL_PDB}
            #"DEMO"
            )
    ENDIF()

    IF (PARAM_FILES)
        FOREACH(FILE_PATH ${PARAM_FILES})
            #Check path type and correct. 
            IF(IS_ABSOLUTE ${FILE_PATH})
                SET(COPY ${FILE_PATH})
            ELSE()
                SET(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_PATH})
            ENDIF()
        
            FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
                IF(IS_DIRECTORY "${COPY}")
                    INSTALL(DIRECTORY ${COPY} DESTINATION ${APP_INSTALL_BIN}/${CONFIG} 
                        #COMPONENT "DEMO"	
                        CONFIGURATIONS ${CONFIG})
                ELSE()
                    INSTALL(FILES ${COPY} DESTINATION ${APP_INSTALL_BIN}/${CONFIG} 
                        #COMPONENT "DEMO"	
                        CONFIGURATIONS ${CONFIG})
                ENDIF()
            ENDFOREACH()
        ENDFOREACH()
    ENDIF()
    
ENDFUNCTION()

#------------------------------------------------------------------------------

FUNCTION(RPLM_INSTALL_CORE)
    SET(ONE_VALUE_ARGS TARGET POSTFIX_INCLUDE POSTFIX_BIN POSTFIX_LIB POSTFIX_PDB)
    
    CMAKE_PARSE_ARGUMENTS(PARAM "" "${ONE_VALUE_ARGS}" "" ${ARGN})
    
    SET(BIN ${APP_INSTALL_BIN})
    SET(LIB ${APP_INSTALL_LIB})
    SET(INCLUDE ${APP_INSTALL_INCLUDE})
    SET(PDB ${APP_INSTALL_PDB})
    
    IF(PARAM_POSTFIX_BIN)
        SET(BIN ${BIN}/${PARAM_POSTFIX_BIN})
    ENDIF()
    
    IF(PARAM_POSTFIX_LIB)
        SET(LIB ${LIB}/${PARAM_POSTFIX_LIB})
    ENDIF()
    
    IF(PARAM_POSTFIX_INCLUDE)
        SET(INCLUDE ${INCLUDE}/${PARAM_POSTFIX_INCLUDE})
    ENDIF()
    
    IF(PARAM_POSTFIX_PDB)
        SET(PDB ${PDB}/${PARAM_POSTFIX_PDB})
    ENDIF()
    
    _PRIVATE_RPLM_INSTALL(${PARAM_TARGET} ${BIN} ${LIB} ${INCLUDE} ${PDB}
        #"DEMO;SDK"
        )
ENDFUNCTION()

#------------------------------------------------------------------------------

FUNCTION(RPLM_INSTALL_BINARY)
    SET(ONE_VALUE_ARGS TARGET CONFIG)
    SET(MULTI_VALUE_ARGS FILES DIRECTORY)
    
    CMAKE_PARSE_ARGUMENTS(PARAM "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    #FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    FOREACH(CONFIG ${CMAKE_INSTALL_CONFIG_NAME})
        IF ((NOT DEFINED PARAM_CONFIG) OR (${PARAM_CONFIG} MATCHES ${CONFIG}))
        #FOREACH (component SDK DEMO)
            SET(LIB ${CMAKE_INSTALL_PREFIX}/${APP_INSTALL_LIB})
            SET(BIN ${CMAKE_INSTALL_PREFIX}/${APP_INSTALL_BIN})
        
            #IF(PARAM_POSTFIX_DEST)
                #SET(BIN ${BIN}/${PARAM_POSTFIX_DEST})
                #SET(LIB ${LIB}/${PARAM_POSTFIX_DEST})
            #ENDIF()
        
            IF(PARAM_FILES)
                INSTALL(FILES ${PARAM_FILES} 
                        DESTINATION ${BIN} 
                        #COMPONENT ${component} 
                        CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
            
            IF(PARAM_DIRECTORY)
                INSTALL(DIRECTORY ${PARAM_DIRECTORY} 
                        DESTINATION ${BIN} 
                        #COMPONENT ${component} 
                        CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
            
            IF(PARAM_TARGET)
                INSTALL(TARGETS ${PARAM_TARGET}
                        RUNTIME DESTINATION ${BIN} 
                            #COMPONENT ${component} 
                            CONFIGURATIONS ${CONFIG}
                        LIBRARY DESTINATION ${BIN} 
                            #COMPONENT ${component} 
                            CONFIGURATIONS ${CONFIG}
                        )	
            ENDIF()
        #ENDFOREACH()
        ENDIF()
    ENDFOREACH()
ENDFUNCTION()

#------------------------------------------------------------------------------

FUNCTION(RPLM_INSTALL_QT5_BIN TARGET_NAME INSTALL_BIN_PATH)

    if ("${QTVERSION}" STREQUAL "Qt5")
        set (QTINSTALLPREFIX ${_qt5Core_install_prefix})
    else()
        set (QTINSTALLPREFIX ${QT6_INSTALL_PREFIX})
    endif()
    message(STATUS "${QTVERSION} install folder = ${QTINSTALLPREFIX}")
    
    IF(WIN32)
        SET(QT5_BINARY_DIR ${QTINSTALLPREFIX}/bin)
        #FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
        FOREACH(CONFIG ${CMAKE_INSTALL_CONFIG_NAME})
            SET(DEBUG_FILE_POSTFIX)
            IF(${CONFIG} STREQUAL Debug)
                SET(DEBUG_FILE_POSTFIX "d")
            ELSE()
                IF(${CONFIG} STREQUAL RelWithDebInfo)
                    SET(DEBUG_FILE_POSTFIX "d")
                ENDIF()
            ENDIF()

            set (QT_LIB ${QTVERSION}Core ${QTVERSION}Gui ${QTVERSION}Widgets ${QTVERSION}PrintSupport ${QTVERSION}Svg 
                    ${QTVERSION}Xml 
                    ${QTVERSION}Pdf ${QTVERSION}Network 
                    ${QTVERSION}PdfWidgets ${QTVERSION}WebEngineCore ${QTVERSION}WebEngine ${QTVERSION}WebEngineWidgets 
                    ${QTVERSION}Quick 
                    ${QTVERSION}QuickWidgets 
                    ${QTVERSION}WebChannel ${QTVERSION}Qml ${QTVERSION}Positioning ${QTVERSION}QmlModels ${QTVERSION}Help ${QTVERSION}Sql 
                    ${QTVERSION}Multimedia ${QTVERSION}MultimediaWidgets
                    ${QTVERSION}Charts
                    ${QTVERSION}OpenGL
                    libGLESv2 libEGL)
            if ("${QTVERSION}" STREQUAL "Qt6")
                list(APPEND QT_LIB ${QTVERSION}Core5Compat)
                list(APPEND QT_LIB ${QTVERSION}SvgWidgets)
                list(APPEND QT_LIB ${QTVERSION}WebEngineQuick)
            endif()
            FOREACH(QT_FILE_NAME ${QT_LIB})
                SET(FILE_PATH ${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}.dll)
                IF(EXISTS "${FILE_PATH}")
                    INSTALL(FILES ${FILE_PATH} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()
            FOREACH(QT_FILE_NAME ${QT_LIB})
                SET(FILE_PATH ${QT5_BINARY_DIR}/${QT_FILE_NAME}.dll)
                IF(EXISTS "${FILE_PATH}")
                    INSTALL(FILES ${FILE_PATH} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()
        
            FOREACH(QT_FILE_NAME QtWebEngineProcess)
                SET(FILE_PATH ${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}.exe)
                IF(EXISTS "${FILE_PATH}")
                    INSTALL(FILES ${FILE_PATH} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()

            FOREACH(QT_PLUGIN_FOLIDER imageformats platforms printsupport iconengines styles sqldrivers platforminputcontexts platformthemes mediaservice)
                IF(EXISTS "${QT5_BINARY_DIR}/../plugins/${QT_PLUGIN_FOLIDER}")
                    SET(COPY_FILES)
                    FILE(GLOB PLUGIN_FILES ${QT5_BINARY_DIR}/../plugins/${QT_PLUGIN_FOLIDER}/*.dll)

                    #FOREACH(f ${PLUGIN_FILES})
                    #	#string(REPLACE "d.dll" "${DEBUG_FILE_POSTFIX}.dll" out ${f})
                    #	LIST(APPEND COPY_FILES ${out}) 
                    #ENDFOREACH()

                    LIST(APPEND COPY_FILES ${PLUGIN_FILES}) 

                    INSTALL(FILES ${COPY_FILES} 
                            DESTINATION ${INSTALL_BIN_PATH}/Qt/plugins/${QT_PLUGIN_FOLIDER} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()

            FOREACH(QT_TRANSLATION_FOLDER translations)
                IF(EXISTS "${QT5_BINARY_DIR}/../${QT_TRANSLATION_FOLDER}")
                    SET(COPY_FILES)
                    FILE(GLOB TRANSLATION_FILES ${QT5_BINARY_DIR}/../${QT_TRANSLATION_FOLDER}/*_en.qm ${QT5_BINARY_DIR}/../${QT_TRANSLATION_FOLDER}/*_ru.qm)

                    LIST(APPEND COPY_FILES ${TRANSLATION_FILES}) 

                    INSTALL(FILES ${COPY_FILES} 
                            DESTINATION ${INSTALL_BIN_PATH}/Qt/${QT_TRANSLATION_FOLDER} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()
            
            FOREACH(QT_WEBENGINE_FOLDER translations/qtwebengine_locales)
                IF(EXISTS "${QT5_BINARY_DIR}/../${QT_WEBENGINE_FOLDER}")
                    SET(COPY_FILES)
                    FILE(GLOB WEBENGINE_FILES ${QT5_BINARY_DIR}/../${QT_WEBENGINE_FOLDER}/en-US.pak ${QT5_BINARY_DIR}/../${QT_WEBENGINE_FOLDER}/ru.pak)

                    LIST(APPEND COPY_FILES ${WEBENGINE_FILES}) 

                    INSTALL(FILES ${COPY_FILES} 
                            DESTINATION ${INSTALL_BIN_PATH}/Qt/${QT_WEBENGINE_FOLDER} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()
            
            FOREACH(QT_RESOURCES_FOLDER resources)
                IF(EXISTS "${QT5_BINARY_DIR}/../${QT_RESOURCES_FOLDER}")
                    SET(COPY_FILES)
                    FILE(GLOB RESOURCES_FILES ${QT5_BINARY_DIR}/../${QT_RESOURCES_FOLDER}/*.*)

                    LIST(APPEND COPY_FILES ${RESOURCES_FILES}) 

                    INSTALL(FILES ${COPY_FILES} 
                            DESTINATION ${INSTALL_BIN_PATH}/Qt/${QT_RESOURCES_FOLDER} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()
            
            INSTALL(DIRECTORY ${QT5_BINARY_DIR}/.
                    DESTINATION ${INSTALL_BIN_PATH}
                    #COMPONENT DEMO
                    CONFIGURATIONS ${CONFIG}
                    FILES_MATCHING PATTERN "icu*.dll"
                        #PATTERN "icu*.dll"
                        #PATTERN "icu*.dll"
                     
                    )
        ENDFOREACH()
    ELSE()
        string(TOLOWER ${QTVERSION} QTVERSIONlo)
        if (EXISTS "${QTINSTALLPREFIX}/lib/x86_64-linux-gnu/lib${QTVERSION}Core.so")
            # install astra Qt
            SET(QT5_BINARY_DIR ${QTINSTALLPREFIX}/lib/x86_64-linux-gnu)
            SET(QT5_BINARYEXEC_DIR ${QTINSTALLPREFIX}/lib/x86_64-linux-gnu/${QTVERSIONlo}/libexec)
            SET(QT5_ADD_FILES libicui18n.so.63 libicuuc.so.63 libicudata.so.63)
        ELSE()
            # install ubuntu, debian Qt
            SET(QT5_BINARY_DIR ${QTINSTALLPREFIX}/lib)
            SET(QT5_BINARYEXEC_DIR ${QTINSTALLPREFIX}/libexec)
            SET(QT5_ADD_FILES libicui18n.so libicuuc.so libicudata.so)
        ENDIF()

        set(QT_LIB lib${QTVERSION}Core lib${QTVERSION}DBus lib${QTVERSION}Gui lib${QTVERSION}Widgets lib${QTVERSION}PrintSupport lib${QTVERSION}Svg 
            lib${QTVERSION}Xml lib${QTVERSION}XcbQpa 
            lib${QTVERSION}Pdf lib${QTVERSION}Network lib${QTVERSION}PdfWidgets lib${QTVERSION}WebEngine lib${QTVERSION}WebEngineCore 
            lib${QTVERSION}WebEngineWidgets lib${QTVERSION}Quick lib${QTVERSION}QuickWidgets 
            lib${QTVERSION}WebChannel lib${QTVERSION}Qml lib${QTVERSION}Positioning lib${QTVERSION}QmlModels lib${QTVERSION}Help lib${QTVERSION}Sql 
            lib${QTVERSION}Multimedia lib${QTVERSION}MultimediaWidgets
            lib${QTVERSION}OpenGL lib${QTVERSION}MultimediaGstTools
            lib${QTVERSION}Charts
            libGLESv2 libEGL)
            if ("${QTVERSION}" STREQUAL "Qt6")
                list(APPEND QT_LIB lib${QTVERSION}Core5Compat)
                list(APPEND QT_LIB lib${QTVERSION}SvgWidgets)
                list(APPEND QT_LIB lib${QTVERSION}WebEngineQuick)
            endif()
        FOREACH(QT_FILE_NAME ${QT_LIB})
            #message("${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}.so")
            SET(FILE_PATH ${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}.so)
            get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
            IF(EXISTS "${_resolvedFile}")
                INSTALL(FILES ${_resolvedFile} 
                        DESTINATION ${INSTALL_BIN_PATH} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            else()
                SET(FILE_PATH ${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}.so.5)
                get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
                IF(EXISTS "${_resolvedFile}")
                    INSTALL(FILES ${_resolvedFile} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            #CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDIF()
        ENDFOREACH()

        FOREACH(QT_FILE_NAME QtWebEngineProcess)
            #message("${QT5_BINARYEXEC_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}.so")
            SET(FILE_PATH ${QT5_BINARYEXEC_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX})
            get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
            IF(EXISTS "${_resolvedFile}")
                INSTALL(FILES ${_resolvedFile} 
                        DESTINATION ${INSTALL_BIN_PATH} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
        ENDFOREACH()

        FOREACH(QT_FILE_NAME ${QT5_ADD_FILES})
            #message("${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX}")
            SET(FILE_PATH ${QT5_BINARY_DIR}/${QT_FILE_NAME}${DEBUG_FILE_POSTFIX})
            get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
            IF(EXISTS "${_resolvedFile}")
                INSTALL(FILES ${_resolvedFile} 
                        DESTINATION ${INSTALL_BIN_PATH} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
        ENDFOREACH()
        
        FOREACH(QT_PLUGIN_FOLDER imageformats platforms printsupport iconengines xcbglintegrations sqldrivers platforminputcontexts platformthemes mediaservice)
            set (QT_COMPONENT "${QTINSTALLPREFIX}/plugins/${QT_PLUGIN_FOLDER}")
            IF(NOT EXISTS "${QT_COMPONENT}")
                set (QT_COMPONENT "${QT5_BINARY_DIR}/${QTVERSIONlo}/plugins/${QT_PLUGIN_FOLDER}") 
            ENDIF()

            IF(EXISTS "${QT_COMPONENT}")
                SET(COPY_FILES)
                FILE(GLOB PLUGIN_FILES ${QT_COMPONENT}/*.so)

                #FOREACH(f ${PLUGIN_FILES})
                #	#string(REPLACE "d.dll" "${DEBUG_FILE_POSTFIX}.dll" out ${f})
                #	LIST(APPEND COPY_FILES ${out}) 
                #ENDFOREACH()

                LIST(APPEND COPY_FILES ${PLUGIN_FILES}) 

                INSTALL(FILES ${COPY_FILES} 
                        DESTINATION ${INSTALL_BIN_PATH}/Qt/plugins/${QT_PLUGIN_FOLDER} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            ELSE()
                message(STATUS "Not exist = ${QT_COMPONENT}")
            ENDIF()
        ENDFOREACH()

        FOREACH(QT_TRANSLATION_FOLDER translations)
            set (QT_TRANSLATIONS "${QTINSTALLPREFIX}/${QT_TRANSLATION_FOLDER}")
            if (NOT EXISTS ${QT_TRANSLATIONS})
                set (QT_TRANSLATIONS "${QTINSTALLPREFIX}/share/${QTVERSIONlo}/${QT_TRANSLATION_FOLDER}")
            ENDIF()
            IF(EXISTS "${QT_TRANSLATIONS}")
                SET(COPY_FILES)
                FILE(GLOB TRANSLATION_FILES ${QT_TRANSLATIONS}/*_en.qm ${QT_TRANSLATIONS}/*_ru.qm)

                LIST(APPEND COPY_FILES ${TRANSLATION_FILES}) 

                INSTALL(FILES ${COPY_FILES} 
                        DESTINATION ${INSTALL_BIN_PATH}/Qt/${QT_TRANSLATION_FOLDER} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
        ENDFOREACH()
            
        FOREACH(QT_WEBENGINE_FOLDER translations/qtwebengine_locales)
            set (QT_WEBENGINE "${QTINSTALLPREFIX}/${QT_WEBENGINE_FOLDER}")
            if (NOT EXISTS ${QT_WEBENGINE})
                set (QT_WEBENGINE "${QTINSTALLPREFIX}/share/${QTVERSIONlo}/${QT_WEBENGINE_FOLDER}")
            ENDIF()
            IF(EXISTS "${QT_WEBENGINE}")
                SET(COPY_FILES)
                FILE(GLOB WEBENGINE_FILES ${QT_WEBENGINE}/en-US.pak ${QT_WEBENGINE}/ru.pak)

                LIST(APPEND COPY_FILES ${WEBENGINE_FILES}) 

                INSTALL(FILES ${COPY_FILES} 
                        DESTINATION ${INSTALL_BIN_PATH}/Qt/${QT_WEBENGINE_FOLDER} 
                        #DESTINATION ${INSTALL_BIN_PATH}/qtwebengine_locales 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
        ENDFOREACH()
            
        FOREACH(QT_RESOURCES_FOLDER resources)
            set (QT_RESOURCES "${QTINSTALLPREFIX}/${QT_RESOURCES_FOLDER}")
            if (NOT EXISTS ${QT_RESOURCES})
                set (QT_RESOURCES "${QTINSTALLPREFIX}/share/${QTVERSIONlo}/${QT_RESOURCES_FOLDER}")
            ENDIF()
            IF(EXISTS "${QT_RESOURCES}")
                SET(COPY_FILES)
                FILE(GLOB RESOURCES_FILES ${QT_RESOURCES}/*.*)

                LIST(APPEND COPY_FILES ${RESOURCES_FILES}) 

                INSTALL(FILES ${COPY_FILES} 
                        DESTINATION ${INSTALL_BIN_PATH}/Qt/${QT_RESOURCES_FOLDER} 
                        #DESTINATION ${INSTALL_BIN_PATH} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()
        ENDFOREACH()
            
        #INSTALL(DIRECTORY ${QT5_BINARY_DIR}/.
        #        DESTINATION ${INSTALL_BIN_PATH}
        #        #COMPONENT DEMO
        #        CONFIGURATIONS ${CONFIG}
        #        FILES_MATCHING PATTERN "icu*.so"
        #            #PATTERN "icu*.dll"
        #            #PATTERN "icu*.dll"
        #             
        #        )
    ENDIF()
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_POCO_BIN TARGET_NAME INSTALL_BIN_PATH)

    message(STATUS "Poco folder =${Poco_ROOT_DIR}")

    IF(WIN32)
        FOREACH(CONFIG ${CMAKE_INSTALL_CONFIG_NAME})
        #FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
            SET(DEBUG_FILE_POSTFIX)
            IF(${CONFIG} STREQUAL Debug)
                SET(DEBUG_FILE_POSTFIX "d")
            ELSE()
                IF(${CONFIG} STREQUAL RelWithDebInfo)
                    SET(DEBUG_FILE_POSTFIX "d")
                ENDIF()
            ENDIF()
        
            IF ( EXISTS "${Poco_ROOT_DIR}/bin64" )
                SET(POCO_BIN "${Poco_ROOT_DIR}/bin64")
                #list(APPEND poco_components libssl libcrypto PocoUtil64 PocoFoundation64 PocoSQL64 PocoCppUnit64 PocoNet64 PocoJSON64 PocoNetSSL64 PocoDataPostgreSQL64 PocoXML64 PocoCrypto64 PocoData64 PocoJWT64 PocoZip64)
                list(APPEND poco_components libssl libcrypto PocoUtil64 PocoFoundation64 PocoNet64 PocoJSON64 PocoNetSSL64 PocoDataPostgreSQL64 PocoXML64 PocoCrypto64 PocoData64 PocoJWT64 PocoZip64)
            ELSEIF ( EXISTS "${Poco_ROOT_DIR}/bin" )
                SET(POCO_BIN "${Poco_ROOT_DIR}/bin")
                #list(APPEND poco_components libssl libcrypto PocoUtil PocoFoundation PocoSQL PocoCppUnit PocoNet PocoJSON PocoNetSSL PocoDataPostgreSQL PocoXML PocoCrypto PocoData PocoJWT PocoZip)
                list(APPEND poco_components libssl libcrypto PocoUtil PocoFoundation PocoNet PocoJSON PocoNetSSL PocoDataPostgreSQL PocoXML PocoCrypto PocoData PocoJWT PocoZip)
            ENDIF ()
            
            FOREACH(POCO_FILE_NAME ${poco_components})
                SET(FILE_PATH ${POCO_BIN}/${POCO_FILE_NAME}${DEBUG_FILE_POSTFIX}.dll)
                IF(EXISTS "${FILE_PATH}")
                    INSTALL(FILES ${FILE_PATH} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            CONFIGURATIONS ${CONFIG}
                            )
                ENDIF()
            ENDFOREACH()

        ENDFOREACH()
    ELSE()
        FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
            SET(DEBUG_FILE_POSTFIX)
            IF(${CONFIG} STREQUAL Debug)
                SET(DEBUG_FILE_POSTFIX)# "d")
            ELSE()
                IF(${CONFIG} STREQUAL RelWithDebInfo)
                    SET(DEBUG_FILE_POSTFIX)# "d")
                ENDIF()
            ENDIF()
        
            FOREACH(POCO_FILE_NAME libPocoFoundation libPocoNet libPocoUtil libPocoData libPocoCppParser libPocoCrypto libPocoNetSSL libPocoXML libPocoJSON libPocoDataPostgreSQL libPocoJWT libPocoZip)
                SET(FILE_PATH /lib/${POCO_FILE_NAME}${DEBUG_FILE_POSTFIX}.so)
                get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
                IF(EXISTS "${_resolvedFile}")
                    INSTALL(FILES ${_resolvedFile} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            #CONFIGURATIONS ${CONFIG}
                            )
                else()
                    #try to install from /usr/local/lib
                    SET(FILE_PATH /usr/local/lib/${POCO_FILE_NAME}${DEBUG_FILE_POSTFIX}.so)
                    get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
                    IF(EXISTS "${_resolvedFile}")
                        INSTALL(FILES ${_resolvedFile} DESTINATION ${INSTALL_BIN_PATH})
                    endif()
                ENDIF()
            ENDFOREACH()

        ENDFOREACH()
    ENDIF()
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_POSTGRESQL_BIN TARGET_NAME INSTALL_BIN_PATH RPLM_CMAKE)
    
    IF(WIN32)	
        FOREACH(POSTGRESQL_FILE_NAME libeay32 libiconv libintl libpq ssleay32)
            SET(FILE_PATH $ENV{PostgreSQL_ROOT}/bin/${POSTGRESQL_FILE_NAME}.dll)
            IF(EXISTS "${FILE_PATH}")
                INSTALL(FILES ${FILE_PATH} 
                        DESTINATION ${INSTALL_BIN_PATH} 
                        #COMPONENT DEMO
                        CONFIGURATIONS ${CONFIG}
                        )
            
            ENDIF()
        ENDFOREACH()
    ELSE()
        FOREACH(POSTGRESQL_FILE_NAME libssl libcrypto libpq)
            SET(FILE_PATH /usr/lib/x86_64-linux-gnu/${POSTGRESQL_FILE_NAME}.so)
            get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
            IF(EXISTS "${_resolvedFile}")
                INSTALL(FILES ${_resolvedFile} 
                        DESTINATION ${INSTALL_BIN_PATH} 
                        #COMPONENT DEMO
                        #CONFIGURATIONS ${CONFIG}
                        )
            
            ENDIF()
        ENDFOREACH()
    ENDIF()
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_SERVER_CONFIG TARGET_NAME INSTALL_BIN_PATH)
    INSTALL(DIRECTORY  ${PROJECT_SOURCE_DIR}/${TARGET_NAME}/cert DESTINATION ${INSTALL_BIN_PATH} CONFIGURATIONS ${CONFIG})
    INSTALL(DIRECTORY  ${PROJECT_SOURCE_DIR}/${TARGET_NAME}/config DESTINATION ${INSTALL_BIN_PATH} CONFIGURATIONS ${CONFIG})
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_CONFIG TARGET_NAME INSTALL_BIN_PATH)
    INSTALL(DIRECTORY  ${PROJECT_SOURCE_DIR}/${TARGET_NAME}/config DESTINATION ${INSTALL_BIN_PATH} CONFIGURATIONS ${CONFIG})
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_MKL_BIN TARGET_NAME INSTALL_BIN_PATH)

    message(STATUS "MKL folder =${INTEL_COMPILER_DIR}")
    
    IF(WIN32)
        
        FOREACH(MKL_FILE_NAME libimalloc libiomp5md mkl_avx mkl_avx2 mkl_avx512 mkl_core mkl_def mkl_intel_thread mkl_mc mkl_mc3 mkl_rt)
            IF(EXISTS "${INTEL_COMPILER_DIR}/redist/intel64_win/mkl/${MKL_FILE_NAME}.dll")
                SET(FILE_PATH "${INTEL_COMPILER_DIR}/redist/${mklvers}/mkl/${MKL_FILE_NAME}.dll")
            ELSEIF(EXISTS "${INTEL_COMPILER_DIR}/redist/${mklvers}/compiler/${MKL_FILE_NAME}.dll")
                SET(FILE_PATH "${INTEL_COMPILER_DIR}/redist/${mklvers}/compiler/${MKL_FILE_NAME}.dll")
            ENDIF()
            IF(EXISTS "${FILE_PATH}")
                INSTALL(FILES ${FILE_PATH} 
                        DESTINATION ${INSTALL_BIN_PATH}
                        )
            ENDIF()
        ENDFOREACH()
    ELSE() #linux
        if(NOT DEFINED ENV{SKRBuild})#topsystem
            FOREACH(MKL_FILE_NAME libmkl_intel_lp64 libmkl_core libmkl_def libmkl_gnu_thread libmkl_avx512)
                IF(EXISTS "${INTEL_MKL_DIR}/lib/${mklvers}/${MKL_FILE_NAME}.so")
                    SET(FILE_PATH "${INTEL_MKL_DIR}/lib/${mklvers}/${MKL_FILE_NAME}.so")
                ENDIF()
                IF(EXISTS "${FILE_PATH}")
                    INSTALL(FILES ${FILE_PATH} 
                            DESTINATION ${INSTALL_BIN_PATH}
                            )
                ENDIF()
            ENDFOREACH()
        else() #skr
            FOREACH(MKL_FILE_NAME libmkl_intel_lp64 libmkl_core libmkl_def libmkl_gnu_thread libmkl_avx512 libmkl_intel_thread libiomp5)
                IF(EXISTS "${INTEL_MKL_DIR}/lib/${mklvers}/${MKL_FILE_NAME}.so")
                    SET(FILE_PATH "${INTEL_MKL_DIR}/lib/${mklvers}/${MKL_FILE_NAME}.so")
                ELSEIF(EXISTS "${INTEL_COMPILER_DIR}/lib/${mklvers}/${MKL_FILE_NAME}.so")
                    SET(FILE_PATH "${INTEL_COMPILER_DIR}/lib/${mklvers}/${MKL_FILE_NAME}.so")
                ENDIF()
                IF(EXISTS "${FILE_PATH}")
                    INSTALL(FILES ${FILE_PATH} 
                            DESTINATION ${INSTALL_BIN_PATH}
                            )
                ENDIF()
            ENDFOREACH()
        endif()
    ENDIF()
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_SPACEMOUSE_BIN TARGET_NAME INSTALL_BIN_PATH)

    message(STATUS "SpaceMouse folder =${SPACEMOUSE_INCLUDE_DIR}")
    
    IF(WIN32)
        SET(SPACEMOUSE_BINARY_DIR ${SPACEMOUSE_INCLUDE_DIR}/../lib/bin)
        #message(STATUS "SpaceMouse folder =${SPACEMOUSE_BINARY_DIR}")
        SET(FILE_PATH ${SPACEMOUSE_BINARY_DIR}/TDx.SpaceMouse.Navigation3D.dll)
        IF(EXISTS "${FILE_PATH}")
            INSTALL(FILES ${FILE_PATH}
                    DESTINATION ${INSTALL_BIN_PATH} 
                    )
        ENDIF()
    ELSE()
    ENDIF()
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_OPENCV_BIN TARGET_NAME INSTALL_BIN_PATH)

    message(STATUS "OpenCV folder =${OPENCV_INCLUDE_DIR}")
    
    IF(WIN32)
        #FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
        FOREACH(CONFIG ${CMAKE_INSTALL_CONFIG_NAME})
            SET(DEBUG_FILE_POSTFIX)
            IF(${CONFIG} STREQUAL Debug)
                SET(DEBUG_FILE_POSTFIX "d")
            ELSE()
                IF(${CONFIG} STREQUAL RelWithDebInfo)
                    SET(DEBUG_FILE_POSTFIX "d")
                ENDIF()
            ENDIF()
        
            SET(OPENCV_BINARY_DIR ${OPENCV_INCLUDE_DIR}/../Windows/x64)
            #message(STATUS "OpenCV folder =${OPENCV_BINARY_DIR}")
            SET(FILE_PATH ${OPENCV_BINARY_DIR}/opencv_world454${DEBUG_FILE_POSTFIX}.dll)
            IF(EXISTS "${FILE_PATH}")
                INSTALL(FILES ${FILE_PATH}
                        DESTINATION ${INSTALL_BIN_PATH} 
                        CONFIGURATIONS ${CONFIG}
                        )
            ENDIF()

        ENDFOREACH()
    ELSE()
        FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
            SET(DEBUG_FILE_POSTFIX)
            IF(${CONFIG} STREQUAL Debug)
                SET(DEBUG_FILE_POSTFIX)# "d")
            ELSE()
                IF(${CONFIG} STREQUAL RelWithDebInfo)
                    SET(DEBUG_FILE_POSTFIX)# "d")
                ENDIF()
            ENDIF()
        
            FOREACH(OPENCV_FILE_NAME libopencv_core libopencv_videoio libopencv_imgcodecs libopencv_imgproc libtbb)
                if(NOT DEFINED ENV{SKRBuild})
                    SET(FILE_PATH /lib/${OPENCV_FILE_NAME}${DEBUG_FILE_POSTFIX}.so)
                else ()
                    SET(FILE_PATH /lib/x86_64-linux-gnu/${OPENCV_FILE_NAME}${DEBUG_FILE_POSTFIX}.so)
                endif()
                get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
                IF(EXISTS "${_resolvedFile}")
                    INSTALL(FILES ${_resolvedFile} 
                            DESTINATION ${INSTALL_BIN_PATH} 
                            #COMPONENT DEMO
                            #CONFIGURATIONS ${CONFIG}
                            )
                else()
                    #try to install from /usr/local/lib
                    SET(FILE_PATH /usr/local/lib/${OPENCV_FILE_NAME}${DEBUG_FILE_POSTFIX}.so)
                    get_filename_component(_resolvedFile "${FILE_PATH}" REALPATH)
                    IF(EXISTS "${_resolvedFile}")
                        INSTALL(FILES ${_resolvedFile} DESTINATION ${INSTALL_BIN_PATH})
                    endif()
                ENDIF()
            ENDFOREACH()

        ENDFOREACH()
    ENDIF()
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_PYTHON_API TARGET_NAME)
    #message(STATUS "target=${TARGET_NAME}")

    #RPLM_INSTALL_CORE(TARGET ${TARGET_NAME}
    #    POSTFIX_INCLUDE ${TARGET_NAME} 
    #    POSTFIX_BIN $<IF:$<CONFIG:Debug>,PythonAPI.d,$<IF:$<CONFIG:RelWithDebInfo>,PythonAPI.rd,PythonAPI>> 
    #    POSTFIX_LIB $<IF:$<CONFIG:Debug>,PythonAPI.d,$<IF:$<CONFIG:RelWithDebInfo>,PythonAPI.rd,PythonAPI>>)
    RPLM_INSTALL_CORE(TARGET ${TARGET_NAME}
        POSTFIX_INCLUDE ${TARGET_NAME})
ENDFUNCTION()

FUNCTION(RPLM_INSTALL_PYTHON_LIBRARY)

    if (WIN32)
        INSTALL(
            FILES
                ${Python3_RUNTIME_LIBRARY_RELEASE}
                ${Python3_RUNTIME_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}.dll
            DESTINATION
                ${APP_INSTALL_BIN}
            )
    elseif(UNIX)
    #    INSTALL(
    #        FILES
    #            ${Python3_LIBRARY}
    #        DESTINATION
    #            ${APP_INSTALL_BIN}
    #        NAMELINK_SKIP
    #        )
        get_filename_component(_resolvedFile "${Python3_LIBRARY_RELEASE}" REALPATH)
        INSTALL(
            FILES
                ${_resolvedFile}
            DESTINATION
                ${APP_INSTALL_BIN}
            )
    endif()

    # Install Python common lib
    if (WIN32)
        set(PYTHON_LIBRARY_BASE_PY ${Python3_RUNTIME_LIBRARY_DIRS}/Lib)
        set(PYTHON_LIBRARY_TKINTER ${Python3_RUNTIME_LIBRARY_DIRS}/tcl)
        set(PYTHON_DISTPACKAGES ${Python3_RUNTIME_LIBRARY_DIRS}/Lib/site-packages)
    else(UNIX)
        set(PYTHON_LIBRARY_BASE_PY ${Python3_STDLIB})
        set(PYTHON_LIBRARY_TKINTER /usr/share/tcltk)

        message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-home folder : $ENV{HOME}")

        set(site_folders 
            $ENV{HOME}/.local/lib/python3.6/site-packages
            $ENV{HOME}/.local/lib/python3.7/site-packages
            $ENV{HOME}/.local/lib/python3.8/site-packages
            /usr/local/lib/python3.6/dist-packages 
            /usr/local/lib/python3.7/dist-packages 
            /usr/local/lib/python3.8/dist-packages 
            /usr/lib/python3/dist-packages 
            )
        foreach (package_folder ${site_folders})
            message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-search dist-packages folder : ${package_folder}")
            if (EXISTS "${package_folder}/requests")
                set (PYTHON_DISTPACKAGES ${package_folder})
                break()
            endif()
        endforeach()
   
    endif()

    set(PYTHON_SCRIPT_LIB_FILE encodings collections importlib logging tkinter json http email urllib)
    FOREACH(LIB_NAME ${PYTHON_SCRIPT_LIB_FILE})
        file(GLOB FILE_LIB ${PYTHON_LIBRARY_BASE_PY}/${LIB_NAME}/*.py)
        INSTALL(FILES
            ${FILE_LIB}
        DESTINATION
            ${APP_INSTALL_BIN}/PythonLib/${LIB_NAME}
        )
    endforeach()
    
    set(PYTHON_SCRIPT_LIB_DIR ctypes multiprocessing xml)
    FOREACH(LIB_NAME ${PYTHON_SCRIPT_LIB_DIR})
        set(DIR_LIB ${PYTHON_LIBRARY_BASE_PY}/${LIB_NAME})
        INSTALL(DIRECTORY
                    ${DIR_LIB}
                DESTINATION
                    ${APP_INSTALL_BIN}/PythonLib
                COMPONENT   copy-files
                PATTERN __pycache__ EXCLUDE
                PATTERN test EXCLUDE
                PATTERN fetch* EXCLUDE
                PATTERN README* EXCLUDE
               )
    endforeach()
    
    set(TK_SCRIPT_LIB_FILE tcl8.6 tcl8.6/encoding tk8.6 tk8.6/ttk)
    FOREACH(LIB_NAME ${TK_SCRIPT_LIB_FILE})
        file(GLOB FILE_LIB 
            ${PYTHON_LIBRARY_TKINTER}/${LIB_NAME}/*.tcl 
            ${PYTHON_LIBRARY_TKINTER}/${LIB_NAME}/*.c 
            ${PYTHON_LIBRARY_TKINTER}/${LIB_NAME}/tclIndex
            ${PYTHON_LIBRARY_TKINTER}/${LIB_NAME}/*.enc
            )
        INSTALL(FILES
                    ${FILE_LIB}
                DESTINATION
                    ${APP_INSTALL_BIN}/PythonLib/${LIB_NAME}
                )
    endforeach()

    #file(GLOB PYTHON_LIBRARY_FILES_ENCOD ${PYTHON_LIBRARY_BASE_PY}/encodings/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_COL ${PYTHON_LIBRARY_BASE_PY}/collections/*.py)
    #set(PYTHON_LIBRARY_FILES_CTYPES ${PYTHON_LIBRARY_BASE_PY}/ctypes)
    #set(PYTHON_LIBRARY_FILES_MP ${PYTHON_LIBRARY_BASE_PY}/multiprocessing)
    #file(GLOB PYTHON_LIBRARY_FILES_IMP ${PYTHON_LIBRARY_BASE_PY}/importlib/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_LOG ${PYTHON_LIBRARY_BASE_PY}/logging/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_TKINTER ${PYTHON_LIBRARY_BASE_PY}/tkinter/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_JSON ${PYTHON_LIBRARY_BASE_PY}/json/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_HTTP ${PYTHON_LIBRARY_BASE_PY}/http/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_EMAIL ${PYTHON_LIBRARY_BASE_PY}/email/*.py)
    #file(GLOB PYTHON_LIBRARY_FILES_TCL ${PYTHON_LIBRARY_TKINTER}/tcl8.6/*.tcl ${PYTHON_LIBRARY_TKINTER}/tcl8.6/*.c ${PYTHON_LIBRARY_TKINTER}/tcl8.6/tclIndex)
    #file(GLOB PYTHON_LIBRARY_FILES_TK ${PYTHON_LIBRARY_TKINTER}/tk8.6/*.tcl ${PYTHON_LIBRARY_TKINTER}/tk8.6/*.c ${PYTHON_LIBRARY_TKINTER}/tk8.6/tclIndex)
    #file(GLOB PYTHON_LIBRARY_FILES_TTK ${PYTHON_LIBRARY_TKINTER}/tk8.6/ttk/*.tcl)

    # 12.10.2022
    if (EXISTS ${PYTHON_DISTPACKAGES}/requests)
        message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-exist folder : ${PYTHON_DISTPACKAGES}/requests")
        set(REQUEST_LIB requests certifi idna defusedxml lml odf pyexcel_ods)
        foreach(LIB_NAME ${REQUEST_LIB})
            file(GLOB FILE_LIB ${PYTHON_DISTPACKAGES}/${LIB_NAME}/*.*)
            INSTALL(FILES
                        ${FILE_LIB}
                    DESTINATION
                        ${APP_INSTALL_BIN}/PythonLib/${LIB_NAME}
                   )
        endforeach()
        
        set(REQUEST_DIR requests chardet urllib3 pyexcel_io)
        foreach(LIB_NAME ${REQUEST_DIR})
            set (DIR_LIB "${PYTHON_DISTPACKAGES}/${LIB_NAME}")
            INSTALL(DIRECTORY
                        ${DIR_LIB}
                    DESTINATION
                        ${APP_INSTALL_BIN}/PythonLib
                    COMPONENT   copy-files
                    PATTERN __pycache__ EXCLUDE
                   )
        endforeach()
        
        #file(GLOB PYTHON_LIBRARY_FILES_REQUESTS ${PYTHON_DISTPACKAGES}/requests/*.*)
        #file(GLOB PYTHON_LIBRARY_FILES_CERTIFI ${PYTHON_DISTPACKAGES}/certifi/*.*)
        #file(GLOB PYTHON_LIBRARY_FILES_IDNA ${PYTHON_DISTPACKAGES}/idna/*.*)
        #set (PYTHON_LIBRARY_FILES_CHARDET "${PYTHON_DISTPACKAGES}/chardet")
        #set (PYTHON_LIBRARY_FILES_URLLIB3 "${PYTHON_DISTPACKAGES}/urllib3")
        if (EXISTS "${PYTHON_DISTPACKAGES}/six.py")
            file(GLOB PYTHON_LIBRARY_FILES_SIX ${PYTHON_DISTPACKAGES}/six.py)
        endif()
    endif()
    #---- 12.10.2022

    if (WIN32)
        file(GLOB PYTHON_LIBRARY_FILES ${PYTHON_LIBRARY_BASE_PY}/*.py)
        #file(GLOB PYTHON_LIBRARY_FILES_PYD ${Python3_RUNTIME_LIBRARY_DIRS}/DLLs/_tkinter.pyd)
        if (EXISTS ${PYTHON_DISTPACKAGES}/PyQt5)
            message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-exist folder : ${PYTHON_DISTPACKAGES}/PyQt5")
            file(GLOB PYTHON_LIBRARY_FILES_PYQT5 
                ${PYTHON_DISTPACKAGES}/PyQt5/*.py 
                ${PYTHON_DISTPACKAGES}/PyQt5/*.pyd
                ${PYTHON_DISTPACKAGES}/PyQt5/*.pyi
                )
        endif()

        foreach( dll_file _tkinter.pyd tcl86t.dll tk86t.dll _ctypes.pyd _multiprocessing.pyd libffi-7.dll _socket.pyd select.pyd _queue.pyd unicodedata.pyd pyexpat.pyd)
            if (EXISTS "${Python3_RUNTIME_LIBRARY_DIRS}/DLLs/${dll_file}")
                list(APPEND PYTHON_LIBRARY_FILES_PYD ${Python3_RUNTIME_LIBRARY_DIRS}/DLLs/${dll_file})
            endif()
        endforeach()
    else(UNIX)
        message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-python stdlib folder =${Python3_STDLIB}")

        file(GLOB PYTHON_LIBRARY_FILES1 ${Python3_STDLIB}/*.py)
        set(PYTHON_LIBRARY_FILES)
        foreach( py_file ${PYTHON_LIBRARY_FILES1} )
            get_filename_component(_resolvedPyFile "${py_file}" REALPATH)
            #message(${_resolvedPyFile})
            list(APPEND PYTHON_LIBRARY_FILES ${_resolvedPyFile})
        endforeach()
        file(GLOB PYTHON_LIBRARY_FILES_SO1 
            ${Python3_STDLIB}/lib-dynload/_tkinter.* 
            /usr/lib/libBLT.2.5.so.8.6 
            /usr/lib/x86_64-linux-gnu/libtk8.6.so
            /usr/lib/x86_64-linux-gnu/libtcl8.6.so
            ${Python3_STDLIB}/lib-dynload/_ctypes.* #_ctypes.cpython-38-x86_64-linux-gnu.so
            ${Python3_STDLIB}/lib-dynload/_multiprocessing.* #_multiprocessing.cpython-38-x86_64-linux-gnu.so
            /usr/lib/x86_64-linux-gnu/libffi.so) #.6)
        set(PYTHON_LIBRARY_FILES_SO)
        foreach( so_file ${PYTHON_LIBRARY_FILES_SO1} )
            get_filename_component(_resolvedSoFile "${so_file}" REALPATH)
            #message(${_resolvedSoFile})
            list(APPEND PYTHON_LIBRARY_FILES_SO ${_resolvedSoFile})
        endforeach()
        #message(STATUS "so lib : ${PYTHON_LIBRARY_FILES_SO}")
    
        foreach (package_folder ${site_folders})
            message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-search folder : ${package_folder}")
            if (EXISTS "${package_folder}/PyQt5")
                set (PYTHON_PYQT5 ${package_folder}/PyQt5)
                break()
            endif()
        endforeach()

        file(GLOB PYTHON_LIBRARY_FILES_PYQT5 
            ${PYTHON_PYQT5}/*.py 
            ${PYTHON_PYQT5}/*.so
            ${PYTHON_PYQT5}/*.pyi
            )
        set (rename_sip)
        foreach (sip_so ${PYTHON_LIBRARY_FILES_PYQT5})
            if (${sip_so} MATCHES "sip.cpython*")
                set(rename_sip ${sip_so})
                message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-find sip in list = ${rename_sip}")
                get_filename_component(full_sip_name ${rename_sip} ABSOLUTE)
                list(REMOVE_ITEM PYTHON_LIBRARY_FILES_PYQT5 "${full_sip_name}")
                break()
            endif()
        endforeach()
        #message(STATUS "PyQt5 : ${PYTHON_LIBRARY_FILES_PYQT5}")
        if (EXISTS ${rename_sip})
            message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-rename sip = ${rename_sip} to sip.so")
            INSTALL(FILES
                ${rename_sip}
            DESTINATION
                ${APP_INSTALL_BIN}/PythonLib/PyQt5
            RENAME
                sip.so
            )
        else()
            message(STATUS "LOG(RPLM_INSTALL_PYTHON_LIBRARY)-sip NOT FOUND")
        endif()

        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_LIB ${Python3_PYQT5}/Qt5/lib/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_TRANSLATIONS ${Python3_PYQT5}/Qt5/translations/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_1 ${Python3_PYQT5}/Qt5/plugins/iconengines/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_2 ${Python3_PYQT5}/Qt5/plugins/imageformats/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_3 ${Python3_PYQT5}/Qt5/plugins/platforms/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_4 ${Python3_PYQT5}/Qt5/plugins/platformthemes/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_5 ${Python3_PYQT5}/Qt5/plugins/printsupport/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_6 ${Python3_PYQT5}/Qt5/plugins/sqldrivers/*.*)
        # file(GLOB PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_7 ${Python3_PYQT5}/Qt5/plugins/styles/*.*)

    endif()

    #message("${PYTHON_LIBRARY_FILES}")
    #message("${PYTHON_LIBRARY_FILES_ENCOD}")

    INSTALL(FILES
                ${PYTHON_LIBRARY_FILES}
            DESTINATION
                ${APP_INSTALL_BIN}/PythonLib
            )
    INSTALL(FILES
                ${PYTHON_LIBRARY_FILES_SIX}
            DESTINATION
                ${APP_INSTALL_BIN}/PythonLib
           )
 
    if (WIN32)
        FOREACH(CONFIG ${CMAKE_INSTALL_CONFIG_NAME})
            IF(${CONFIG} STREQUAL Debug)
                SET(INSTALL_FOLDER "PythonAPI.d")
            ELSEIF(${CONFIG} STREQUAL RelWithDebInfo)
                SET(INSTALL_FOLDER "PythonAPI.rd")
            ELSE()
                SET(INSTALL_FOLDER "PythonAPI")
            ENDIF()
            INSTALL(FILES
                        ${PYTHON_LIBRARY_FILES_PYD}
                    DESTINATION
                        ${APP_INSTALL_BIN}/${INSTALL_FOLDER}
                    CONFIGURATIONS 
                        ${CONFIG}
                   )
            INSTALL(FILES
                        ${PYTHON_LIBRARY_FILES_PYD}
                    DESTINATION
                        ${APP_INSTALL_BIN}
                    CONFIGURATIONS 
                        ${CONFIG}
                   )
        ENDFOREACH()
    else()
        INSTALL(FILES
                    ${PYTHON_LIBRARY_FILES_SO}
                DESTINATION
                    ${APP_INSTALL_BIN}
               )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_LIB}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/lib
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_TRANSLATIONS}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/translations
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_1}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/iconengines
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_2}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/imageformats
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_3}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/platforms
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_4}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/platformthemes
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_5}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/printsupport
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_6}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/sqldrivers
            # )
        # INSTALL(FILES
                # ${PYTHON_LIBRARY_FILES_PYQT5_QT5_PLUGINS_7}
            # DESTINATION
                # ${APP_INSTALL_BIN}/PythonLib/PyQt5/Qt5/plugins/styles
            # )
    endif()
ENDFUNCTION()
