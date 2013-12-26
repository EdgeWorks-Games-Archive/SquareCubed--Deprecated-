#include "IUnit.h"

namespace Server {
	namespace Units {
		unsigned int IUnit::nextId = 0;

		IUnit::IUnit() :
			ID(nextId),
			Rotation(),
			GraphicId()
		{
			nextId++;
		}
	}
}