# Generate Header with Config Values
configure_file (
	"${CMAKE_CURRENT_LIST_DIR}/metadata.h.in"
	"${CMAKE_CURRENT_LIST_DIR}/metadata.h"
)

# Get All Files in the current directory to Build
file (GLOB CommonLib_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group ("" FILES
	metadata.h.in
	metadata.h
)
source_group (DataTypes FILES
	agenttypes.h
	postypes.h
	worldtypes.h
)
source_group (Network FILES
	PacketTypes.h
	PhysicsPacketDataTypes.h
)
source_group (Utils\\Events FILES Events.h)
source_group (Utils\\Logger FILES
	Logger.h Logger.cpp
	ILoggingManager.h
	LoggingManager.h LoggingManager.cpp
)

# Add Library Build Output
add_library (CommonLib ${CommonLib_SRC})

# Set Directory
SET_PROPERTY(TARGET CommonLib PROPERTY FOLDER "Common")