#pragma once

#include "Types.h"

namespace Server {
	namespace Units {
		namespace AI {
			class ITask {
			public:
				virtual ~ITask() {}
				virtual void Update(const float delta, AIUnit &unit) = 0;
			};
		}
	}
}