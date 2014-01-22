# Get All Files to Build
file(GLOB ServerRakNetNetwork_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group ("" FILES
	IRakNetPacketHandler.h
	RakNetClientID.h RakNetClientID.cpp
	RakNetNetwork.h RakNetNetwork.cpp
	RakNetNetworkFactory.h RakNetNetworkFactory.cpp
	RakNetNetworkLoader.h
)
source_group ("Packet Dispatchers" FILES
	UnitsDispatcher.h UnitsDispatcher.cpp
	PlayerDispatcher.h PlayerDispatcher.cpp
	WorldDispatcher.h WorldDispatcher.cpp
)
source_group ("Packet Handlers" FILES
	DebugPacketHandler.h DebugPacketHandler.cpp
	PlayerPacketHandler.h PlayerPacketHandler.cpp
	UnitSelectPacketHandler.h UnitSelectPacketHandler.cpp
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