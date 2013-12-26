# Add Current Directory as Include
include_directories (${CMAKE_CURRENT_LIST_DIR})

# Add Projects
add_subdirectory (CommonLib)
add_subdirectory (CRakNetNetwork)
add_subdirectory (Physics)