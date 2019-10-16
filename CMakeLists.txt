set(CMAKE_CXX_STANDARD            14)
set(CMAKE_CXX_STANDARD_REQUIRED   YES)
cmake_minimum_required(VERSION 3.8)

project(PnPGui)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Point CMake where to look for module files.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
include(LoguruLibrary)
add_subdirectory(Application)

set(PNPGUI_SOURCES
    src/PnPGui.cpp
)

source_group("" FILES ${PNPGUI_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PNPGUI_SOURCES})

set(APP_TYPE)
if (WIN32)
    set(APP_TYPE WIN32)

    set(ApplicationIcon ${CMAKE_SOURCE_DIR}/Resources/Icon.ico)
    file(TO_NATIVE_PATH "${ApplicationIcon}" ApplicationIcon)
    string(REPLACE "\\" "\\\\" ApplicationIcon "${ApplicationIcon}")
    configure_file(
        ${CMAKE_SOURCE_DIR}/Resources/Resource.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
    )
    set(PNPGUI_RESOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
    )
elseif (APPLE)
    set(APP_TYPE MACOSX_BUNDLE)

    file(GLOB PNPGUI_RESOURCES "${CMAKE_SOURCE_DIR}/Data/*")
    set_source_files_properties(${PNPGUI_RESOURCES} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/Data"
    )
    set(_Example_Icon "${CMAKE_SOURCE_DIR}/Resources/Icon.icns")
    list(APPEND PNPGUI_RESOURCES ${_Example_Icon})
    set_source_files_properties(${_Example_Icon} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
endif()

add_executable(PnPGui ${APP_TYPE} ${PNPGUI_SOURCES} ${PNPGUI_RESOURCES})

find_package(imgui REQUIRED)
find_package(imgui_node_editor REQUIRED)
find_package(blueprint-utilities)
target_link_libraries(PnPGui PRIVATE imgui imgui_node_editor Application blueprint-utilities)

set(PNPGUI_BIN_DIR ${CMAKE_BINARY_DIR}/Bin)
set_loguru(PnPGui)

set_target_properties(PnPGui PROPERTIES
    FOLDER "Examples"
    RUNTIME_OUTPUT_DIRECTORY                "${PNPGUI_BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${PNPGUI_BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PNPGUI_BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${PNPGUI_BIN_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${PNPGUI_BIN_DIR}"
    DEBUG_POSTFIX                           _d
    RELWITHDEBINGO_POSTFIX                  _rd
    MINSIZEREL_POSTFIX                      _r
    VS_DEBUGGER_WORKING_DIRECTORY           ${PNPGUI_BIN_DIR}
    MACOSX_BUNDLE_INFO_PLIST                "${CMAKE_SOURCE_DIR}/Resources/Info.plist.in"
    MACOSX_BUNDLE_BUNDLE_NAME               "${PACKAGE_NAME}"
    MACOSX_BUNDLE_GUI_IDENTIFIER            "com.sandbox.collisions"
    MACOSX_BUNDLE_LONG_VERSION_STRING       "${PACKAGE_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING      "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}"
    MACOSX_BUNDLE_ICON_FILE                 Icon.icns
)

add_custom_command(
    TARGET PnPGui
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${PNPGUI_BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ARGS ${CMAKE_SOURCE_DIR}/Data ${PNPGUI_BIN_DIR}/Data
)
