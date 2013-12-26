# Get All Files to Build
file(GLOB WorldServerBase_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group (Units FILES
	Units.h Units.cpp
	IUnit.h IUnit.cpp
)
source_group ("Units\\Unit Types" FILES
	BaseUnitTypes.h BaseUnitTypes.cpp
)
source_group (Core FILES
	WorldServer.h WorldServer.cpp
)
source_group (Misc FILES
	gdefines.h
)
source_group (Network FILES
	IClientID.h
	INetwork.h
	INetworkFactory.h
	IPacketHandler.h
)
source_group ("Network\\Handler Callbacks" FILES
	IPlayerCallback.h
)
source_group ("Network\\Packet Dispatchers" FILES
	IUnitsDispatcher.h
	IPlayerDispatcher.h
	IWorldDispatcher.h
)
source_group (Players FILES
	Players.h Players.cpp
)
source_group (World FILES
	World.h World.cpp
)

# Add Library Build Output
add_library (WorldServerBase ${WorldServerBase_SRC})

# Link Required Libraries
target_link_libraries (WorldServerBase CommonLib)
target_link_libraries (WorldServerBase Physics)

# Set Directory
set_property (TARGET WorldServerBase PROPERTY FOLDER "Server")