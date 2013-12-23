# Get All Files to Build
file(GLOB ClientBase_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (ClientBase ${ClientBase_SRC})

# Link Required Libraries
target_link_libraries (ClientBase CommonLib)

# Add Output to Link Directories
link_directories (${PROJECT_BINARY_DIR}/ClientBase)

# Set Directory
SET_PROPERTY(TARGET ClientBase PROPERTY FOLDER "Client")