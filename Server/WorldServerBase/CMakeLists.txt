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
target_link_libraries (WorldServerBase Physics)

# Set Directory
set_property (TARGET WorldServerBase PROPERTY FOLDER "Server")