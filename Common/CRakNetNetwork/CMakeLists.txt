# Get All Files in the current directory to Build
file (GLOB CRakNetNetwork_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups

# Add Library Build Output
add_library (CRakNetNetwork ${CRakNetNetwork_SRC})

# Set Directory
set_property (TARGET CRakNetNetwork PROPERTY FOLDER "Common")