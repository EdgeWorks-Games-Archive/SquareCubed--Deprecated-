#include "IAgent.h"

namespace Server {
	namespace Agents {
		unsigned int IAgent::nextId = 0;

		IAgent::IAgent() :
			ID(nextId),
			Rotation(),
			GraphicId()
		{
			nextId++;
		}
	}
}