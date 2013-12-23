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

# Set Directory
set_property (TARGET ClientBase PROPERTY FOLDER "Client")