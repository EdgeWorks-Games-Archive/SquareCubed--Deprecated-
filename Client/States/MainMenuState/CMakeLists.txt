# Get All Files to Build
file(GLOB MainMenuState_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (MainMenuState ${MainMenuState_SRC})

# Link Required Libraries
target_link_libraries (MainMenuState ClientBase)

# Set Directory
set_property (TARGET MainMenuState PROPERTY FOLDER "Client/States")