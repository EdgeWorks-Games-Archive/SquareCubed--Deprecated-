# Get All Files to Build
file(GLOB ClientRakNetNetwork_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (ClientRakNetNetwork ${ClientRakNetNetwork_SRC})

# Link Required Libraries
target_link_libraries (ClientRakNetNetwork ClientBase)
target_link_libraries (ClientRakNetNetwork RakNet)

# Add Required Library Include Folders
include_directories (${DEPENDENCY_DIR}/RakNet/Source)

# Set Directory
set_property (TARGET ClientRakNetNetwork PROPERTY FOLDER "Client/Modules")