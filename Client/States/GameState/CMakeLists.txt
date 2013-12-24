# Get All Files to Build
file(GLOB GameState_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (GameState ${GameState_SRC})

# Link Required Libraries
target_link_libraries (GameState ClientBase)
target_link_libraries (GameState Physics)

# Set Directory
set_property (TARGET GameState PROPERTY FOLDER "Client/States")