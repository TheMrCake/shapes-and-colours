cmake_minimum_required(VERSION 3.11)

project(shapes_and_colours CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Add SFML
add_subdirectory(lib/SFML)

# Add SFML
add_subdirectory(lib/box2d)

# Source directories
add_subdirectory(src)

# Installer
install(
  TARGETS shapes_and_colours
  DESTINATION .
  RUNTIME DESTINATION .)

install(TARGETS sfml-graphics sfml-window sfml-system sfml-audio box2d
        RUNTIME DESTINATION .)

install(DIRECTORY "resources/" DESTINATION "resources/")

# CPack variables from previously incorrectly generated config These make sure
# to override SFML's configuration

set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_INNOSETUP "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "${CMAKE_SOURCE_DIR};${CMAKE_BINARY_DIR}")
unset(CPACK_CMAKE_GENERATOR)
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
unset(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE)
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY
    "shapes_and_colours built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "NSIS")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};${PROJECT_NAME};ALL;/")
unset(CPACK_INSTALL_PREFIX)
set(CPACK_MODULE_PATH "")
set(CPACK_MONOLITHIC_INSTALL "ON")
set(CPACK_NSIS_CONTACT "")
set(CPACK_NSIS_DISPLAY_NAME "Shapes and Colours")
set(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "${PROGRAMFILES64}")
unset(CPACK_NSIS_PACKAGE_NAME)
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
unset(CPACK_PACKAGE_DESCRIPTION_FILE)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "shapes_and_colours built using CMake")
set(CPACK_PACKAGE_FILE_NAME "shapes_and_colours_installer")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "shapes_and_colours")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "shapes_and_colours")
set(CPACK_PACKAGE_NAME "shapes_and_colours")
set(CPACK_PACKAGE_NAME_SUMMARY "A game about shapes and colours")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Team P")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
unset(CPACK_RESOURCE_FILE_LICENSE)
unset(CPACK_RESOURCE_FILE_README)
unset(CPACK_RESOURCE_FILE_WELCOME)
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

# Turns out calling this generates the CPack config so it needs to be below the
# configuration settings
include(CPack)
