#pragma once

#include <WorldServerBase/IClientID.h>

#include <RakNetTypes.h>

namespace Server {
	namespace RakNetNetwork {
		struct RakNetClientID : public Network::IClientID {
			RakNet::RakNetGUID GUID;

			RakNetClientID(RakNet::RakNetGUID guid) : GUID(guid) {}

			bool operator==(const IClientID& par);
			Network::IClientID* Clone() const;
			const std::string ToString() const;
		};
	}
}