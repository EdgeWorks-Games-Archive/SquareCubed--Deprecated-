# Get All Files to Build
file(GLOB ServerRakNetNetwork_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (ServerRakNetNetwork ${ServerRakNetNetwork_SRC})

# Link Required Libraries
target_link_libraries (ServerRakNetNetwork WorldServerBase)
target_link_libraries (ServerRakNetNetwork RakNet)

# Add Required Library Include Folders
include_directories (${DEPENDENCY_DIR}/RakNet/Source)

# Set Directory
SET_PROPERTY(TARGET ServerRakNetNetwork PROPERTY FOLDER "Server")