# Get All Files to Build
file(GLOB ClientRakNetNetwork_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group ("" FILES
	IRakNetPacketHandler.h
	RakNetNetwork.h RakNetNetwork.cpp
	RakNetNetworkFactory.h RakNetNetworkFactory.cpp
	RakNetNetworkLoader.h
)
source_group ("Packet Dispatchers" FILES
	DebugDispatcher.h DebugDispatcher.cpp
	GameDispatcher.h GameDispatcher.cpp
	PlayerDispatcher.h PlayerDispatcher.cpp
)
source_group ("Packet Handlers" FILES
	UnitsPacketHandler.h UnitsPacketHandler.cpp
	MainMenuPacketHandler.h MainMenuPacketHandler.cpp
	PlayerPacketHandler.h PlayerPacketHandler.cpp
	WorldPacketHandler.h WorldPacketHandler.cpp
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