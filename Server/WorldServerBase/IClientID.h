#pragma once

#include <string>

namespace Server {
	namespace Network {
		struct IClientID {
			virtual ~IClientID() {}
			virtual bool operator==(const IClientID& par) = 0;
			virtual IClientID* Clone() const = 0;
			virtual const std::string ToString() const = 0;
		};
	}
}