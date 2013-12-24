# Add Current Directory as Include
include_directories (${CMAKE_CURRENT_LIST_DIR})

add_subdirectory (ClientBase)
add_subdirectory (Modules)
add_subdirectory (States)
add_subdirectory (Client)