cmake_minimum_required (VERSION 2.8.3)
project (SquareCubed)

# Turn on Solution Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Add Version Variables
set (VERSION_MAJOR 0 CACHE STRING "Major engine version.")
set (VERSION_MINOR 3 CACHE STRING "Minor engine version.")
set (VERSION_PATCH 0 CACHE STRING "Patch engine version.")

# Add Game Root Variable (for installer generation and debugging)
set (GAME_ROOT "" CACHE PATH "Root of the game content for use in installer generation. This won't set working directory, you have to do that manually.")

# Make Sure Game Root Path is Valid
if (NOT EXISTS ${GAME_ROOT}/Content)
	message (SEND_ERROR "Game Root folder does not contain Content directory.")
endif()

# Add Installer Details for Content Root
install (DIRECTORY ${GAME_ROOT}/Bin/ DESTINATION Bin)
install (DIRECTORY ${GAME_ROOT}/Content/ DESTINATION Content)
install (DIRECTORY ${GAME_ROOT}/Logs/ DESTINATION Logs)

# Add Common Defines
add_definitions (-D_USE_MATH_DEFINES)

# Add Dependencies
add_subdirectory (Dependencies)

# Add Dependency Folder as Include Directory
include_directories (${DEPENDENCY_DIR})

# Add Common
add_subdirectory (Common)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/Common")

# Add Client
add_subdirectory (Client)

# Add Server
add_subdirectory (Server)

# Build a CPack driven Installer Package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set (CPACK_PACKAGE_VENDOR "EdgeWorks Games")
include (CPack)