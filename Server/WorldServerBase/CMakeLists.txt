# Get All Files to Build
file(GLOB WorldServerBase_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (WorldServerBase ${WorldServerBase_SRC})

# Link Required Libraries
target_link_libraries (WorldServerBase CommonLib)

# Add Output to Link Directories
link_directories (${PROJECT_BINARY_DIR}/WorldServerBase)

# Set Directory
SET_PROPERTY(TARGET WorldServerBase PROPERTY FOLDER "Server")