cmake_minimum_required (VERSION 2.8.3)
project (SquareCubed)

# Turn on Solution Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Add Version Variables
set (VERSION_MAJOR 0 CACHE STRING "Major engine version.")
set (VERSION_MINOR 3 CACHE STRING "Minor engine version.")
set (VERSION_PATCH 0 CACHE STRING "Patch engine version.")

# Add Temp Game Data Variables
set (GAME_TEMP_CONTROLS_SETTING 0 CACHE STRING "0 for RPG controls, 1 for RTS controls")

# Add Game Root Variable (for installer generation and debugging)
set (GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/GameRoot" CACHE PATH "Root of the game content for use in installer generation. This won't set working directory, you have to do that manually.")

# Make Sure Game Root Path is Valid
if (NOT EXISTS ${GAME_ROOT}/Content)
	message (SEND_ERROR "Game Root folder does not contain Content directory.")
endif()

# Add Installer Details for Content Root
install (DIRECTORY ${GAME_ROOT}/Host/ DESTINATION Host)
install (DIRECTORY ${GAME_ROOT}/Content/ DESTINATION Content)
install (DIRECTORY ${GAME_ROOT}/Logs/ DESTINATION Logs)

# Set Ouput Directory For Debugging
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${GAME_ROOT}/")
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string (TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GAME_ROOT})
endforeach (OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Add Common Defines
add_definitions (-D_USE_MATH_DEFINES)

# Add Dependencies
add_subdirectory (Dependencies)

# Add Dependency Folder as Include Directory
include_directories (${DEPENDENCY_DIR})

# Add Link Folders (Should be moved to the correct files but egh)
link_directories ("${DEPENDENCY_DIR}/glfw/lib")
link_directories ("${DEPENDENCY_DIR}/devil/lib")
link_directories ("${DEPENDENCY_DIR}/glew/lib")
link_directories ("${DEPENDENCY_DIR}/CoherentUI/lib/${DEPENDENCY_COHERENT_LIB_SUBFOLDER}")

# Add Common
add_subdirectory (Common)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/Common")

# Add Client
add_subdirectory (Client)

# Add Server
add_subdirectory (Server)

## Build a CPack driven Installer Package ##

# Runtime Libraries
include (InstallRequiredSystemLibraries)
install (FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION ./ COMPONENT Libraries)
set (CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Runtime Libraries")

# Descriptions
set (CPACK_COMPONENT_LIBRARIES_DESCRIPTION "The runtime libraries required to install SquareCubed client and server.")
set (CPACK_COMPONENT_CLIENT_DESCRIPTION "The client required to connect to servers and play the game.")
set (CPACK_COMPONENT_SERVER_DESCRIPTION "The server required to host games the client can connect to.")

# Start Menu Shortcuts
set (CPACK_NSIS_MENU_LINKS "./Client.exe" "Game Client" "./WorldServer.exe" "World Server")
set (CPACK_PACKAGE_EXECUTABLES "" "")

# MetaData
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VENDOR "EdgeWorks Games(TM)")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

include (CPack)