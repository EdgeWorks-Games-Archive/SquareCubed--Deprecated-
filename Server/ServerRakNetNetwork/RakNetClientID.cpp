#include "RakNetClientID.h"

namespace Server {
	namespace RakNetNetwork {
		bool RakNetClientID::operator==(const IClientID& par) {
			const RakNetClientID& rakpar = static_cast<const RakNetClientID&>(par);
			return this->GUID == rakpar.GUID;
		}

		Network::IClientID* RakNetClientID::Clone() const {
			return new RakNetClientID(*this);
		}

		const std::string RakNetClientID::ToString() const {
			return GUID.ToString();
		}
	}
}