#include <WorldServerBase/WorldServer.h>

#include <ServerRakNetNetwork/RakNetNetworkLoader.h>

#include <CommonLib/LoggingManager.h>

int main(int argc, char* args []) {
	// Initialize Logger
	Utils::ILoggingManager *loggingManager = new Utils::LoggingManager("./Logs/WorldServer.log");
	Utils::Logger logger = loggingManager->CreateLogger("Loader");

	logger.LogHighlight("Initializing all World Server Modules...");

	// Set up Network Module
	Server::Network::INetwork *network = Server::RakNetNetwork::LoadNetwork(*loggingManager, 6789, 16);

	logger.LogHighlight("All Engine Modules Initialized");
	logger.LogHighlight("Initializing World Server...");

	// Initialize World Server
	Server::Core::WorldServer worldServer(loggingManager, network);

	logger.LogHighlight("World Server Initialized");

	// Run World Server
	worldServer.Execute();
}