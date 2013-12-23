cmake_minimum_required (VERSION 2.8.3)
project (SquareCubed)

# Turn on Solution Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Add Version Variables
set (VERSION_MAJOR 3 CACHE STRING "Major engine version.")
set (VERSION_MINOR 0 CACHE STRING "Minor engine version.")
set (VERSION_PATCH 0 CACHE STRING "Patch engine version.")

# Add Dependencies
include_directories (Dependencies)

# Add Dependency Folder as Include Directory
include_directories (${DEPENDENCY_DIR})

# Add Common
add_subdirectory (Common)
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/Common")

# Add Client
add_subdirectory (Client)

# Build a CPack driven Installer Package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set (CPACK_PACKAGE_VENDOR "EdgeWorks Games")
include (CPack)